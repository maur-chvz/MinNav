#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/minnav.sock"
#define IT_TIMES 10

int main() {

    printf("Starting PING PONG test...\n");

    int clientfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(clientfd == -1) {
        fprintf(stderr, "Failed to create Client Socket: %s\n", strerror(errno));
        return -1;
    }

    struct sockaddr_un addr;
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

    int ret = connect(clientfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret != 0) {
        fprintf(stderr, "Failed to connect Client Socket: %s\n", strerror(errno));
        return -1;
    }

    
    const char* msg = "PING";
    char buff[1024];
    ssize_t bytes = 0;

    for(int i = 0; i < IT_TIMES; ++i) {
        bytes = send(clientfd, msg, strlen(msg), 0);
        printf("Sent %zu bytes of Data\n", bytes);
        sleep(10);
        bytes = recv(clientfd, buff, sizeof(buff) - 1, MSG_DONTWAIT);
        if(bytes > 0) {
            buff[bytes] = '\0';
            printf("[SERVER] %s\n", buff);
        }
        else {
            printf("No data received...\n");
        }
    }
    close(clientfd);
    
    return 0;
}
