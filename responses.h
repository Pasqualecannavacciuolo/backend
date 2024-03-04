#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef RESPONSES_H
#define RESPONSES_H

// Prototipi delle funzioni
char* send_get_response();

/**
 * Formatta una risposta HTTP con il corpo JSON specificato.
 * La funzione prende il corpo JSON come parametro e genera una stringa che rappresenta
 * una risposta HTTP con intestazioni appropriate e il corpo JSON specificato.
 *
 * @param jsonBody Il corpo JSON da includere nella risposta HTTP.
 * @return Puntatore a una stringa allocata dinamicamente contenente la risposta HTTP formattata.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 *         Se si verifica un errore durante l'allocazione di memoria, la funzione restituirà NULL.
 */
char* format_http_response(char* jsonBody);

#endif
