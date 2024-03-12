#include "handlers.h"

void handle_client(int client_fd)
{
    // IMPORTANTE - assegnare un buffer sufficientemente grande per evitare effetti indesiderati (stampe caratteri non voluti es: �X�)
    char buffer[4096];
    ssize_t bytes_received;

    // Leggi la richiesta HTTP dal client
    bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes_received < 0) {
        perror("Errore durante la lettura della richiesta HTTP");
        close(client_fd);
        return;
    }

    // Aggiungi il terminatore di stringa al buffer
    buffer[bytes_received] = '\0';

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

    handle_request_by_endpoint(client_fd, endpoint);

    // Chiudi la connessione con il client
    //close(client_fd);
}

void handle_request_by_endpoint(int client_fd, const char *endpoint)
{
    if (strcmp(endpoint, "/libreria") == 0)
    {
        get_all_libri(client_fd);
    }
    else if (strcmp(endpoint, "/prestiti") == 0)
    {
        get_all_prestiti(client_fd);
    }
    else if (strcmp(endpoint, "/utenti") == 0)
    {
        get_all_utenti(client_fd);
    }
    else
    {
        // Gestione per endpoint sconosciuto
        char *response = format_http_response(404, "Questo endpoint non e' stato registrato");
        send(client_fd, response, strlen(response), 0);
        log_to_success("GET", endpoint, "404");
        free(response);
    }
    //close(client_fd);
}

/*void handle_int_signal(int socket_descriptor)
{
    printf("\nRicevuto segnale SIGINT. Terminazione del server...\n");
    close(socket_descriptor);
    exit(EXIT_SUCCESS);
}*/

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

    // Validazione dell'endpoint per prevenire buffer overflow
    size_t path_length = strlen(path);
    if (path_length >= 256)
    {
        return -1; // Errore: lunghezza dell'endpoint troppo lunga
    }

    // Copia l'endpoint estratto nella stringa 'endpoint'
    strncpy(endpoint, path, path_length);
    endpoint[strlen(path)] = '\0'; // Assicura che la stringa sia terminata correttamente

    return 0; // Parsing della richiesta HTTP completato con successo
}
