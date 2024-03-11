#ifndef MAIN_H
#define MAIN_H

// Includi i file di intestazione necessari
#include <sys/wait.h>

#include "handlers.h"
#include "responses.h"
#include "endpoints/libreria.h"
#include "formatters/libro.h"
#include "endpoints/prestiti.h"
#include "formatters/prestito.h"
#include "log/logging.h"

#define PROTOCOL_PORT 5193
#define QUEUE_LEN 10

int socket_descriptor;
struct sockaddr_in server_address;
struct sockaddr_in client_address;
socklen_t client_address_len = sizeof(client_address);

#endif
