#ifndef DRAW_H_
#define DRAW_H_

#include "gfc_primitives.h"

#include "model.h"
#include "gf3d_mesh.h"

typedef struct{
    Model* cube;
    Model* sphere;
    Model* cylinder;
}DrawData;


void draw3d_draw_init(void);
void draw3d_draw_sphere(GFC_Sphere sphere, GFC_Color colorMod);

#endif // DRAW_H_
