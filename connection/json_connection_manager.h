#ifndef JSON_CONNECTION_MANAGER_H
#define JSON_CONNECTION_MANAGER_H

// Includi le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int connect_to_json_server(const char *json_server_ip, int json_server_port);

#endif