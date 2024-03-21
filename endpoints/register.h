#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../log/logging.h"
#include "../responses.h"

#define JSON_SERVER_IP "192.168.1.53"
#define JSON_SERVER_PORT 5555

#ifndef REGISTER_H
#define REGISTER_H


// Struttura dati per rappresentare un utente
typedef struct {
    char nome[100];
    char cognome[100];
    char nome_utente[100];
    char data_nascita[11]; // "YYYY-MM-DD"
    char codice_fiscale[17];
    char email[100];
    char password[100];
    char tipo_utente[20]; // "Studente" o "Libraio"
} Utentee;

void register_user(int client_socket, const char *json_body);

#endif