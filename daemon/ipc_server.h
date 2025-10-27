#ifndef IPC_SERVER_H
#define IPC_SERVER_H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdbool.h>

#define UPDATE_INTERVAL 10
#define SOCKET_PATH "/tmp/minnav.sock"
#define LOGNAME "TESTL"

void* ipc_server_start(void* arg);
void ipc_server_stop();
#endif
