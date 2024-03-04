#ifndef HANDLERS_H
#define HANDLERS_H

// Includi le librerie necessarie
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "responses.h"

// Prototipi delle funzioni
void handle_client(int client_fd);
void handle_int_signal(int socket_descriptor);

#endif
