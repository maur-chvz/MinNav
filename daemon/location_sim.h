#ifndef LOCATION_SIM_H
#define LOCATION_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "log.h"

#define MAX_LAT 90.0
#define MIN_LAT -90.0
#define MAX_LON 180.0
#define MIN_LON -180.0

//lat=40.7128, lon=-74.0060, timestamp=2025-10-24T13:35:00Z
typedef struct {
    double lat;
    double lon;
    char timestamp[80];
} Coordinate;

double genRandom();
void update_latitude(Coordinate* co);
void update_longitude(Coordinate* co);
void update_coordinates(Coordinate* co);
void location_sim_start();
void location_sim_test();


#endif
