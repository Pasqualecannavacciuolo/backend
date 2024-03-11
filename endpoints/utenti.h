#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../log/logging.h"

#define JSON_SERVER_IP "192.168.1.53"
#define JSON_SERVER_PORT 5555

#ifndef UTENTI_H
#define UTENTI_H


/**
 * @brief Ottiene tutti i dati dalla risorsa "utenti" sul server JSON remoto
 *        e li invia al client che ha fatto la richiesta al web server.
 * 
 * @param client_socket Il socket associato alla connessione con il client che ha fatto la richiesta al web server.
 */
void get_all_utenti(int client_socket);

#endif