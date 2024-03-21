#ifndef JSON_CONNECTION_MANAGER_H
#define JSON_CONNECTION_MANAGER_H

// Includi le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define JSON_SERVER_IP "192.168.1.53"
#define JSON_SERVER_PORT 5555

int connect_to_json_server();

#endif