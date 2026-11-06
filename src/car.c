#include "simple_logger.h"
#include "simple_json.h"

#include "model.h"
#include "car.h"
#include "entity.h"

typedef struct{
    CarData* cars;
    Uint32 carCount;
}CarManager;

static CarManager car_manager = {0};

void car_data_init(Uint32 carCount, const char *filename) {

}
