#ifndef __CAR_H_
#define __CAR_H_


#include "gfc_types.h"
#include "gfc_primitives.h"
#include "entity.h"

typedef float Torque;
typedef int RPM;

typedef struct{
    Torque torque;
    RPM rpm;
}GraphPoint;

typedef struct{
    GraphPoint* data;
    Uint32 count;
}TorqueGraph;

typedef struct carData{ //we need so much stuff
    GFC_TextLine name;

    float frontSuspensionStiffness;
    float frontSuspensionLength;
    float rearSuspensionStiffness;
    float rearSuspensionLength;
    float finalDrive;
    float ratios[8][5];
    TorqueGraph torqueGraph;

    GFC_Box body;

    GFC_Box frontLeftWheel;
    GFC_Box frontRightWheel;
    GFC_Box rearLeftWheel;
    GFC_Box rearRightWheel;

    GFC_Vector3D cameraOffset;
    
}CarData;

#define car_data(ent) ((CarData*)((ent)->data))

void car_init(Entity*,const char*, const char*);

Torque car_torque_lookup(TorqueGraph torqueGraph, RPM rpm);

void car_camera_update(Entity* carEnt, GFC_Matrix4 view,int dir);

#endif

