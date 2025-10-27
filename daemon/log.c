#include "log.h"

static Logger logger;

void getTime() {
    time_t rawtime;
    struct tm* info;
    
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(logger.timestamp, sizeof(logger.timestamp), "%Y-%m-%d %H:%M:%S", info);
}


int logger_start() {
    char path[64];
    if(getcwd(path, sizeof(path)) == NULL) {
        fprintf(stderr, "Failed to get current path: %s\n", strerror(errno));
        return -1;
    }

    strcpy(logger.absolute_path, path);
    strcat(logger.absolute_path, LOG_PATH);

    FILE* log_file = fopen(logger.absolute_path, "w");
    if(!log_file) {
        printf("Error opening file\n");
        return -1;
    }

    getTime();
    
    fprintf(log_file, "[%s] %s\n", logger.timestamp, "Starting up logger...");
    fclose(log_file);
    return 0;
}

void log_message(const char* msg, ...) {
    FILE* log_file = fopen(logger.absolute_path, "a"); 

    if(!log_file) {
        printf("Error opening file\n");
        return;
    }

    char buff[1024];
    va_list args;
    va_start(args, msg);
    vsnprintf(buff, sizeof(buff), msg, args);
    va_end(args);
    
    getTime();
    fprintf(log_file, "[%s] %s\n", logger.timestamp, buff);
    fclose(log_file);
}

void logger_stop() {

}
