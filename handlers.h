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
#include "formatters/libro.h"
#include "endpoints/libreria.h"

// Prototipi delle funzioni

/**
 * Gestisce una richiesta HTTP da un client.
 * Legge la richiesta HTTP dal client, stampa la richiesta ricevuta,
 * genera e invia una risposta HTTP statica al client, e chiude la connessione.
 *
 * @param client_fd Il descrittore del file del client connesso.
 */
void handle_client(int client_fd);

/**
 * Gestisce il segnale SIGINT ricevuto per la terminazione del server.
 * La funzione stampa un messaggio di avviso, chiude il descrittore del socket
 * specificato e termina il server con lo stato di uscita EXIT_SUCCESS.
 *
 * @param socket_descriptor Il descrittore del socket da chiudere prima di terminare il server.
 */
void handle_int_signal(int socket_descriptor);

#endif
