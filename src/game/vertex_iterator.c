#include <PR/gbi.h>

#include "vertex_iterator.h"
#include "types.h"
#include "memory.h"
#include "engine/math_util.h"

dl_to_iterate vxit_dl_pool[20];
dl_to_iterate * curr_vxit_dl;
int vxit_dl_count = 0;
u8 vxit_dl_flagged = FALSE;
int vxit_vertex_index = 0;

void vxit_init_vtx_list(Vtx * vertices, int size) {
    for (int i = 0; i < size; i++) {
        curr_vxit_dl->addr[vxit_vertex_index].normal[0] = vertices[i].n.n[0];
        curr_vxit_dl->addr[vxit_vertex_index].normal[1] = vertices[i].n.n[1];
        curr_vxit_dl->addr[vxit_vertex_index].normal[2] = vertices[i].n.n[2];
        vec3f_normalize(curr_vxit_dl->addr[vxit_vertex_index].normal);

        curr_vxit_dl->addr[vxit_vertex_index].position[0] = vertices[i].v.ob[0];
        curr_vxit_dl->addr[vxit_vertex_index].position[1] = vertices[i].v.ob[1];
        curr_vxit_dl->addr[vxit_vertex_index].position[2] = vertices[i].v.ob[2];

        curr_vxit_dl->addr[vxit_vertex_index].pointer = NULL;
        vxit_vertex_index ++;
    }
};

int vxit_add_dl_to_iterator(Gfx * dl_to_add, void (*func_to_add)(Vtx * vertices, int size), struct GraphNode *node) {
    u32 * command_read = (u32 *)segmented_to_virtual(dl_to_add);
    int vxit_gfx_stack_level = 0;
    u8 end_of_list = FALSE;
    u32 * vxit_gfx_stack[40];
    u32 total_size = 0;
    u32 dl_size = 0;

    // Calculate size and allocate memory
    while(!end_of_list) {
        u8 other = TRUE;
        if  ( ((*command_read)>>24) == G_DL)  {
            vxit_gfx_stack[vxit_gfx_stack_level] = command_read+2;
            vxit_gfx_stack_level++;
            command_read = segmented_to_virtual((void *)*(command_read+1));
        }
        if ( ((*command_read)>>24) == G_VTX) {
            int size = (((*command_read)>>12) & 0xFF);
            total_size += (size * sizeof(float_vertex));
            dl_size += sizeof(Gfx);

            other = FALSE;
        }
        if ( ((*command_read)>>24) == G_ENDDL) {
            if (vxit_gfx_stack_level == 0) {
                end_of_list = TRUE;
                dl_size += sizeof(Gfx);
            } else {
                vxit_gfx_stack_level--;
                command_read = vxit_gfx_stack[vxit_gfx_stack_level];
            }
        } else {
            command_read+=2;
            if (other) {
                dl_size += sizeof(Gfx);
            }
        }
    }

    curr_vxit_dl = &vxit_dl_pool[vxit_dl_count];
    vxit_dl_pool[vxit_dl_count].dl[0] = dl_to_add;
    vxit_dl_pool[vxit_dl_count].dl[1] = main_pool_alloc(dl_size,MEMORY_POOL_LEFT);
    vxit_dl_pool[vxit_dl_count].func = func_to_add;
    vxit_dl_pool[vxit_dl_count].node = node;
    vxit_dl_pool[vxit_dl_count].addr = main_pool_alloc(total_size,MEMORY_POOL_LEFT);
    vxit_dl_pool[vxit_dl_count].workingDlIndex = 0;

    vxit_gfx_stack_level = 0;
    end_of_list = FALSE;
    command_read = segmented_to_virtual(dl_to_add);
    vxit_vertex_index = 0;

    Gfx * dl_copy_head = vxit_dl_pool[vxit_dl_count].dl[1];

    // Populate allocated memory with vertices + duplicate dl into memory allocated for dlCopy
    while(!end_of_list) {
        u8 other = TRUE;
        if  ( ((*command_read)>>24) == G_DL)  {
            vxit_gfx_stack[vxit_gfx_stack_level] = command_read+2;
            vxit_gfx_stack_level++;
            command_read = segmented_to_virtual((void *)*(command_read+1));
        }
        if ( ((*command_read)>>24) == G_VTX) {
            int size = (((*command_read)>>12) & 0xFF);

            Vtx * copiedVertexList = main_pool_alloc(size*sizeof(Vtx),MEMORY_POOL_LEFT); //allocate verts for copying
            bcopy(  (Vtx *)segmented_to_virtual((void *)*(command_read+1))  ,copiedVertexList,size*sizeof(Vtx)); //copy the verts

            gSPVertex(dl_copy_head, VIRTUAL_TO_PHYSICAL(copiedVertexList), size, 0);
            dl_copy_head++;

            vxit_init_vtx_list( (Vtx *)segmented_to_virtual((void *)*(command_read+1)), size);

            other = FALSE;
        }
        if ( ((*command_read)>>24) == G_ENDDL) {
            if (vxit_gfx_stack_level == 0) {
                gSPEndDisplayList(dl_copy_head);
                end_of_list = TRUE;
            } else {
                vxit_gfx_stack_level--;
                command_read = vxit_gfx_stack[vxit_gfx_stack_level];
            }
        } else {
            if (other) {
                bcopy((void*)command_read,dl_copy_head,sizeof(Gfx));
                dl_copy_head++;
            }

            command_read+=2;
        }
    }

    vxit_dl_count++;
    return vxit_dl_count-1;
}

Gfx * vxit_iterate_dl(int id) {
    curr_vxit_dl = &vxit_dl_pool[id];
    vxit_vertex_index = 0;

    curr_vxit_dl->workingDlIndex = !curr_vxit_dl->workingDlIndex; //swap

    u32 * command_read;
    if (curr_vxit_dl->workingDlIndex == 0) {
        command_read = segmented_to_virtual(curr_vxit_dl->dl[0]); // original is a physical address
    } else {
        command_read = (u32 *)curr_vxit_dl->dl[1]; // copy is an allocated address, this is why i do this
    }
    u32 * vxit_gfx_stack[40];
    u8 end_of_list = FALSE;
    int vxit_gfx_stack_level = 0;

    while(!end_of_list) {
        if  ( ((*command_read)>>24) == G_DL)  {
            vxit_gfx_stack[vxit_gfx_stack_level] = command_read+2;
            vxit_gfx_stack_level++;

            command_read = segmented_to_virtual((void *)*(command_read+1));
        }
        if ( ((*command_read)>>24) == G_VTX) {
            int size = (((*command_read)>>12) & 0xFF);
            curr_vxit_dl->func( segmented_to_virtual((void *)*(command_read+1)), size);

        }
        if ( ((*command_read)>>24) == G_ENDDL) {
            if (vxit_gfx_stack_level == 0) {
                end_of_list = TRUE;
            } else {
                vxit_gfx_stack_level--;
                command_read = vxit_gfx_stack[vxit_gfx_stack_level];
            }
        } else {
            command_read+=2;
        }
    }

    return curr_vxit_dl->dl[!curr_vxit_dl->workingDlIndex];
}