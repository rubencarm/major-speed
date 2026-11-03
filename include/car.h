#ifndef __CAR_H_
#define __CAR_H_

#include "gfc_types.h"

typedef struct{
    float frontSpringConstant;
    float frontSpringLength;

    float rearSpringConstant;
    float rearSpringLength;

}Suspension;

typedef struct{
    float finalDrive;
    float ratios[8][5]; //[gear][ratio,min_rpm,max_rpm,upshift_rpm,downshift_rpm] 8 gears cause if you need more you're doing too much
}Transmission;

typedef struct{
         
}Engine;

typedef struct carData{
    GFC_TextLine name;
    Suspension suspension;
    Transmission transmission;
    Engine engine;
}CarData;


#endif // CAR_H_
