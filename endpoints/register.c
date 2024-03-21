#include "register.h"

void register_user(int client_socket, const char *json_body) {
    // Connect to JSON server
    int json_socket = connect_to_json_server();
    if (json_socket < 0) {
        perror("Errore nella connessione al server JSON");
        return;
    }

    // Costruisci la richiesta HTTP POST
    char request[4096];
    int request_length = snprintf(request, sizeof(request),
                                  "POST /utenti HTTP/1.1\r\n"
                                  "Host: %s\r\n"
                                  "Content-Type: application/json\r\n"
                                  "Content-Length: %zu\r\n\r\n"
                                  "%s",
                                  JSON_SERVER_IP, strlen(json_body), json_body);

    if (send(json_socket, request, request_length, 0) < 0) {
        perror("Errore nell'invio della richiesta");
        close(json_socket);
        return;
    }

    // Invia l'intestazione HTTP Content-Type al client
    const char *header = "HTTP/1.1 201 CREATED\r\nContent-Type: application/json\r\n\r\n";
    if (send(client_socket, header, strlen(header), 0) < 0) {
        perror("Errore nell'invio dell'intestazione al client");
        close(client_socket);
        close(json_socket);
        return;
    }

    // Invia il corpo della risposta JSON al client
    const char *response_message = "{\"status\": 201, \"messaggio\": \"Utente registrato con successo\"}";
    if (send(client_socket, response_message, strlen(response_message), 0) < 0) {
        perror("Errore nell'invio dei dati al client");
        close(client_socket);
        close(json_socket);
        return;
    }

    log_to_success("POST", "/utenti", "201");

    // Chiusura delle connessioni
    close(json_socket);
}
