#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#include "ipc_server.h"
#include "location_sim.h"
#include "log.h"

int main(int argc, char* argv[]) {

    logger_start();
    location_sim_start();
    
    int ret = daemon(0, 0);
    if(ret != 0) {
        fprintf(stderr, "Failed to create Daemon: %s\n", strerror(errno));
        INFO("Failed to create Daemon: %s\n", strerror(errno));
        return -1;
    }

    pthread_t ipc_server;
    ret = pthread_create(&ipc_server, NULL, ipc_server_start, NULL);
    if(ret != 0) {
        INFO("Failed to start IPC server thread: %s\n", strerror(errno));
        return -1;
    }

    Coordinate co;
    co.lat = 40.0;
    co.lon = -70.0;
    
    for(int i = 0; i < 10; ++i) {
        update_coordinates(&co);
        INFO("lat: %lf, lon: %lf", co.lat, co.lon);
        sleep(12);
    }

    ipc_server_stop();
    logger_stop();
    pthread_join(ipc_server, NULL);
    
    return 0;
}
