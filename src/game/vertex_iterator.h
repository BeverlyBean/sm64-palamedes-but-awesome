#include "types.h"

#ifndef VERTEX_ITERATOR_H
#define VERTEX_ITERATOR_H

typedef struct {
    Vec3f position;
    Vec3f normal;
    void * pointer;
} float_vertex;

typedef struct {
    Gfx * dl[2];
    u8 workingDlIndex;
    void (*func)(Vtx * vertices, int size);
    struct GraphNode *node;
    float_vertex * addr;
} dl_to_iterate;

int vxit_add_dl_to_iterator(Gfx * dl_to_add, void (*func_to_add)(Vtx * vertices, int size), struct GraphNode *node);
Gfx * vxit_iterate_dl(int id);

extern int vxit_vertex_index;
extern dl_to_iterate * curr_vxit_dl;

#endif