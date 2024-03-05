#include "handlers.h"

void handle_client(int client_fd)
{
    // IMPORTANTE - assegnare un buffer sufficientemente grande per evitare effetti indesiderati (stampe caratteri non voluti es: �X�)
    char buffer[4096];
    ssize_t bytes_received;

    // Leggi la richiesta HTTP dal client
    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if (bytes_received < 0)
    {
        fprintf(stderr, "Errore nella lettura della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    // Stampa la richiesta HTTP ricevuta dal client
    printf("Richiesta HTTP ricevuta:\n%s", buffer);

    // Analizza la richiesta HTTP per estrarre l'endpoint
    char endpoint[256]; // Assumendo una lunghezza massima per l'endpoint
    if (extract_endpoint(buffer, endpoint) == -1)
    {
        fprintf(stderr, "Errore nel parsing della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    if (strcmp(endpoint, "/libreria") == 0)
    {
        char *getLibreriaJson = get_all();
        char *response = format_http_response(getLibreriaJson);
        send(client_fd, response, strlen(response), 0);
        free(getLibreriaJson);
        free(response);
    } else if(strcmp(endpoint, "/") == 0) {
        char *response = send_get_response();
        send(client_fd, response, strlen(response), 0);
        free(response);
    }

    // Chiudi la connessione con il client
    close(client_fd);
}

void handle_int_signal(int socket_descriptor)
{
    printf("\nRicevuto segnale SIGINT. Terminazione del server...\n");
    close(socket_descriptor);
    exit(EXIT_SUCCESS);
}

int extract_endpoint(char *request, char *endpoint)
{
    // Controllo degli argomenti
    if (request == NULL || endpoint == NULL)
    {
        return -1; // Errore nei parametri
    }

    // Cerca la prima riga della richiesta HTTP
    char *first_line = strtok(request, "\r\n");
    if (first_line == NULL)
    {
        return -1; // Errore nel parsing della richiesta HTTP
    }

    // Estrae il metodo e l'endpoint dalla prima riga
    char method[16], path[256];
    if (sscanf(first_line, "%s %s", method, path) != 2)
    {
        return -1; // Errore nel parsing della riga della richiesta
    }

    // Copia l'endpoint estratto nella stringa 'endpoint'
    strncpy(endpoint, path, strlen(path));
    endpoint[strlen(path)] = '\0'; // Assicura che la stringa sia terminata correttamente

    return 0; // Parsing della richiesta HTTP completato con successo
}
