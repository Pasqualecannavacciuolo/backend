#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../connection/json_connection_manager.h"
#include "../log/logging.h"
#include "../responses.h"


#ifndef REGISTER_H
#define REGISTER_H


void register_user(int client_socket, const char *json_body);

#endif