#include "location_sim.h"

double genRandom() {
    return rand() % 2 ? drand48() : -drand48();
}

void update_latitude(Coordinate* co) {
    double diff = genRandom();
    co->lat += diff;
    if(co->lat >= MAX_LAT) {
        co->lat =  MIN_LAT + diff;
    }
    else if(co->lat <= MIN_LAT) {
        co->lat = MAX_LAT + diff;
    }
}

void update_longitude(Coordinate* co) {
    double diff = genRandom();
    co->lon += diff;
    if(co->lon >= MAX_LON) {
        co->lon =  MIN_LON + diff;
    }
    else if(co->lon <= MIN_LON) {
        co->lon = MAX_LON + diff;
    }
}

void update_coordinates(Coordinate* co) {
    update_latitude(co);
    update_longitude(co);
}

void location_sim_start() {
    INFO("STARTING LOCATION SIM");
    srand48(time(NULL));
    srand(time(NULL));
}

void location_sim_test() {
    Coordinate co;

    co.lat = 40.7128;
    co.lon = -74.006;
    
    for(int i = 0; i < 100; ++i) {
        update_coordinates(&co);
        INFO("lat: %lf, lon: %lf", co.lat, co.lon);
    }
}
