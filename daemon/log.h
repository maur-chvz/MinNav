#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

#define LOG_PATH "/../logs/test.log"

#define INFO(msg, ...) log_message(msg, ##__VA_ARGS__)

typedef struct {
    FILE* log_file;
    char timestamp[80];
    char absolute_path[128];
} Logger;

void getTime();
int logger_start();
void log_message(const char* msg, ...);
void logger_stop();

#endif
