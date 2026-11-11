#ifndef __LEVEL_H_
#define __LEVEL_H_

#include "gfc_types.h"
#include "gfc_primitives.h"
#include "gfc_audio.h"

#include "model.h"
#include "entity.h"

typedef struct{

    GFC_Box bounds;
    GFC_Vector3D spawnPoint; // might want to switch to a list later
    Model* level;
    GFC_Sound* song;

    GFC_List* entityActiveList;

    
}Level;

#endif // LEVEL_H_
