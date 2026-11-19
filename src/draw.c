#include "simple_json.h"
#include "simple_logger.h"


#include "gfc_matrix.h"
#include "model.h"
#include "draw.h"

static DrawData draw_data = {0};

void draw3d_draw_init(){
    draw_data.cube = model_load("models/primitives/cube.model");
    draw_data.sphere = model_load("models/primitives/sphere.model");
    draw_data.cylinder = model_load("models/primitives/cylinder.model");
}

void draw3d_draw_sphere(GFC_Sphere sphere, GFC_Color colorMod){

    GFC_Matrix4 mat;
    GFC_Vector3D scale = gfc_vector3d(1,1,1);
    scale.x = scale.y = scale.z = sphere.r;
    gfc_matrix4_from_vectors(mat,gfc_vector3d(sphere.x, sphere.y, sphere.z),gfc_vector3d(0,0,0),scale);

    model_highlight_queue_render(draw_data.sphere, mat, colorMod);

}
