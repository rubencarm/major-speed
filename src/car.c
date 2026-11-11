#include "simple_json.h"
#include "simple_logger.h"

#include "../include/car.h"

#include "entity.h"
#include "model.h"

void car_torque_graph_from_filename(CarData *carData, const char *filename);

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

  //slog("t = %g",t);

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

  car_slog_torque_graph("yonda classy", data->torqueGraph);
}

void car_slog_torque_graph(const char *name, TorqueGraph graph) {
  int i, c;
  c = graph.count;
  slog("torque graph: \"%s\"", name);
  for (i = 0; i < c; i++) {
    slog("torque: %g rpm: %d", graph.data[i].torque, graph.data[i].rpm);
  }
}

/*eof@eol*/
