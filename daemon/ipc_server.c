#include "ipc_server.h"
#include "log.h"

volatile bool ipc_server_run = true;

void* ipc_server_start(void* arg) {
        
    INFO("STARTING IPC SERVER");

    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd == -1) {
        INFO("Failed to create Socket: %s\n", strerror(errno));
        return NULL;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    unlink(SOCKET_PATH);

    int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret != 0) {
        INFO("Failed to bind Socket: %s", strerror(errno));
        close(sockfd);
        return NULL;
    }

    ret = listen(sockfd, 4);
    if(ret != 0) {
        INFO("Failed to set Socket to listen: %s", strerror(errno));
        close(sockfd);
        return NULL;
    }

    int clientfd = accept(sockfd, NULL, NULL);
    if(clientfd == -1) {
        INFO("Failed to accept client request: %s", strerror(errno));
        close(sockfd);
        return NULL;
    }

    char buff[1024];
    const char* msg = "PONG";
    ssize_t bytes = 0;
    
    while(ipc_server_run) {
        sleep(UPDATE_INTERVAL);
        // INFO("running...");
        bytes = recv(clientfd, buff, sizeof(buff) - 1, MSG_DONTWAIT);
        if(bytes > 0) {
            buff[bytes] = '\0';
            INFO("Received %zu bytes from client", bytes);
            INFO("[CLIENT] %s", buff);
            bytes = send(clientfd, msg, strlen(msg), 0);
            if(bytes > 0) {
                INFO("[SERVER] %s", msg);                
            }
        }
    }
    INFO("TERMINATING IPC SERVER");
    close(clientfd);
    
    close(sockfd);
    unlink(SOCKET_PATH);
    return NULL;
}

void ipc_server_stop() {
    ipc_server_run = false;
}
