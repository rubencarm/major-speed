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

typedef struct carData{
    GFC_TextLine name;

    float frontSuspensionStiffness;
    float frontSuspensionLength;
    float rearSuspensionStiffness;
    float rearSuspensionLength;
    float finalDrive;
    float ratios[8][5];
    TorqueGraph torqueGraph;

    GFC_Box body; //aabb
    
    GFC_Box frontLeftWheel;
    GFC_Box frontRightWheel;
    GFC_Box rearLeftWheel;
    GFC_Box rearRightWheel;
    
}CarData;

void car_init(Entity*,const char*, const char*);

Torque car_torque_lookup(TorqueGraph torqueGraph, RPM rpm);
#endif

