#include "surface_material.h"
#include "sm64.h"

SurfaceMaterial surfaceMaterialStone = {
    .sound = SOUND_TERRAIN_STONE,
};

SurfaceMaterial surfaceMaterialGrass = {
    .sound = SOUND_TERRAIN_GRASS,
};

SurfaceMaterial surfaceMaterialSand = {
    .sound = SOUND_TERRAIN_SAND,
};

SurfaceMaterial surfaceMaterialSnow = {
    .sound = SOUND_TERRAIN_SNOW,
};

SurfaceMaterial surfaceMaterialWood = {
    .sound = SOUND_TERRAIN_SPOOKY,
};

SurfaceMaterial * surfaceMaterialList[] = {
    &surfaceMaterialStone,
    &surfaceMaterialGrass,
    &surfaceMaterialSand,
    &surfaceMaterialSnow,
    &surfaceMaterialWood,
};