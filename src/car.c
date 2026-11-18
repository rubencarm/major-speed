#include "simple_json.h"
#include "simple_logger.h"

#include "car.h"

#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "entity.h"
#include "model.h"

static void car_torque_graph_from_filename(CarData *carData, const char *filename);

void car_init(Entity *ent, const char *filename, const char *carName) {

  SJson *json = NULL, *data = NULL, *car = NULL;
  const char *str1;

  CarData *carData;

  int i, c;
  slog("car_init");
  if (!ent) {
    slog("no entity to initialize car");
    return;
  }
  if (!filename) {
    slog("no filename for carData");
  }
  if (!carName) {
    slog("no car to get from car data");
  }

  json = sj_load(filename);
  if (!json) {
    slog("failed to load car data");
  }
  data = sj_object_get_value(json, "cars");
  if (!data) {
    slog("no car data");
    sj_free(json);
  }
  c = sj_array_get_count(data);

  for (i = 0; i < c; i++) {
    car = sj_array_get_nth(data, i);
    str1 = sj_object_get_value_as_string(car, "name");

    if (strcmp(str1, carName) == 0) {
      // car found!

      carData = gfc_allocate_array(sizeof(CarData), 1);

      gfc_line_cpy(carData->name, str1);
      str1 = NULL;
      str1 = sj_object_get_value_as_string(car, "power_graph");
      car_torque_graph_from_filename(carData, str1);
      ent->data = carData;
      sj_free(json);
      return;
    }
  }
  slog("car '%s' not found", carName);
  sj_free(json);
  return;
}

Torque car_torque_lookup(TorqueGraph torqueGraph, RPM rpm) {
  int i;
  int c = torqueGraph.count;
  float t;
  GraphPoint high = {0}, low = {0};
  RPM currHigh = 0;

  if (torqueGraph.data == NULL) {
    
    return -0;
  }
  i = 0;
  while((currHigh < rpm) && i < c){
      currHigh = torqueGraph.data[i].rpm;
      high = torqueGraph.data[i];
      if(i > 0){
          low = torqueGraph.data[i - 1];
      }
      i++;
  }
  t = (float)((rpm - low.rpm) / (float)(high.rpm - low.rpm));
  return (1-t)*low.torque + t * high.torque;
}

void car_slog_torque_graph(const char *name, TorqueGraph graph);

void car_torque_graph_from_filename(CarData *data, const char *filename) {

  TorqueGraph torqueGraph = {0};
  SJson *json, *graph, *gpoint;
  int i, c;
  GraphPoint point;
  json = sj_load(filename);
  if (!json) {
    return;
  }

  graph = sj_object_get_value(json, "graph");
  if (!graph) {
    sj_free(json);
  }

  c = sj_array_get_count(graph);

  torqueGraph.data = gfc_allocate_array(sizeof(GraphPoint), c);
  torqueGraph.count = c;

  for (i = 0; i < c; i++) {
    gpoint = sj_array_get_nth(graph, i);
    sj_object_get_value_as_int(gpoint, "rpm", &point.rpm);
    sj_object_get_value_as_float(gpoint, "torque", &point.torque);
    torqueGraph.data[i] = point;
    point.rpm = 0;
    point.torque = 0;
  }
  sj_free(json);

  data->torqueGraph = torqueGraph;

  // car_slog_torque_graph("yonda classy", data->torqueGraph);
}

void car_slog_torque_graph(const char *name, TorqueGraph graph) {
  int i, c;
  c = graph.count;
  slog("torque graph: \"%s\"", name);
  for (i = 0; i < c; i++) {
    slog("torque: %g rpm: %d", graph.data[i].torque, graph.data[i].rpm);
  }
}

void car_camera_update(Entity *carEnt, GFC_Matrix4 view, int dir){

    GFC_Vector3D forward = {0};
    GFC_Vector3D cameraPos = {0};

    forward.x = carEnt->mat[0][1];
    forward.y = carEnt->mat[1][1];
    forward.z = carEnt->mat[2][1];

    if(dir){

        if(dir == 1){
            gfc_vector3d_rotate_about_z(&forward,4.71239);
        }
        if(dir == 2){
            gfc_vector3d_rotate_about_z(&forward,1.5081);
        }

    }

    gfc_vector3d_normalize(&forward);
    gfc_vector3d_negate(forward,forward); //backwards now lol
    gfc_vector3d_set_magnitude(&forward,20);
    gfc_vector3d_add(cameraPos,carEnt->position,forward);
    gfc_vector3d_add(cameraPos,cameraPos,gfc_vector3d(0,0,3));
    gfc_matrix4_view(view,cameraPos,carEnt->position,gfc_vector3d(0,0,1));

}

void car_physics_update(Entity* carEnt, float throttle, float brake, float steering){



}

/*eof@eol*/
