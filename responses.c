#include "responses.h"

char* format_http_response(int status, char* jsonBody) {
    size_t httpResponseSize = strlen("HTTP/1.1 XXX \r\n") + strlen("Content-Type: application/json\r\n") +
                              strlen("Content-Length: ") + strlen(jsonBody) + strlen("\r\n\r\n") + 1;

    char *httpResponse = (char *)malloc(httpResponseSize);
    if (httpResponse == NULL) {
        return NULL; // Gestione dell'errore di allocazione di memoria
    }

    // Costruzione della risposta HTTP
    sprintf(httpResponse, "HTTP/1.1 %d ", status); // Inserisce lo status nella risposta

    // Aggiungi il Content-Type
    strcat(httpResponse, "\r\nContent-Type: application/json\r\n");

    // Aggiungi la lunghezza del corpo della risposta
    sprintf(httpResponse + strlen(httpResponse), "Content-Length: %ld\r\n", strlen(jsonBody));

    // Aggiungi fine delle intestazioni e inizio del corpo della risposta
    strcat(httpResponse, "\r\n");
    strcat(httpResponse, jsonBody);

    return httpResponse;
}
