#include "handlers.h"

// Prototipi delle funzioni
void handle_client(int client_fd);
void handle_int_signal(int socket_descriptor);

void handle_client(int client_fd) {
    char buffer [1024];
    ssize_t bytes_received;

    // Leggi la richiesta HTTP dal client
    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if(bytes_received < 0) {
        fprintf(stderr, "Errore nella lettura della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    // Stampa la richiesta HTTP ricevuta dal client
    printf("Richiesta HTTP ricevuta:\n%s", buffer);

    // Invia una risposta HTTP statica al client
    char *response = send_get_response();
    send(client_fd, response, strlen(response), 0);
    free(response);

    // Chiudi la connessione con il client
    close(client_fd);
}

void handle_int_signal(int socket_descriptor) {
    printf("\nRicevuto segnale SIGINT. Terminazione del server...\n");
    close(socket_descriptor);
    exit(EXIT_SUCCESS);
}
