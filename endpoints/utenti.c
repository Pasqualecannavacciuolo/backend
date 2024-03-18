#include "utenti.h"


void get_all_utenti(int client_socket) {
    char buffer[4096] = {0};

    // Connect to JSON server
    int json_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (json_socket < 0) {
        log_to_error("GET", "/utenti", "500", "Errore nella creazione del socket");
        perror("Errore nella creazione del socket");
        return; 
    }

    struct sockaddr_in json_server_addr;
    json_server_addr.sin_family = AF_INET;
    json_server_addr.sin_port = htons(JSON_SERVER_PORT);
    // Con inet_pton converto l'indirizzo nella rappresentazione binaria corretta
    if (inet_pton(AF_INET, JSON_SERVER_IP, &json_server_addr.sin_addr) <= 0) {
        log_to_error("GET", "/utenti", "502", "Indirizzo errato / non supportato");
        perror("Indirizzo errato / non supportato");
        close(json_socket);
        return;
    }

    if (connect(json_socket, (struct sockaddr *)&json_server_addr, sizeof(json_server_addr)) < 0) {
        log_to_error("GET", "/utenti", "503", "Connessione al server fallita");
        perror("Connessione al server fallita");
        close(json_socket);
        return;
    }

    // Send request to JSON server
    char *request = "GET /utenti HTTP/1.1\r\nHost: 192.168.1.53:5555\r\n\r\n";
    if (send(json_socket, request, strlen(request), 0) < 0) {
        log_to_error("GET", "/utenti", "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta al server JSON");
        close(json_socket);
        return;
    }

    // Receive response from JSON server and send to client
    ssize_t bytes_received;
    while ((bytes_received = read(json_socket, buffer, sizeof(buffer))) > 0) {
        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            log_to_error("GET", "/utenti", "505", "Errore nell'invio dei dati al client");
            perror("Errore nell'invio dei dati al client");
            close(json_socket);
            return;
        }
        memset(buffer, 0, sizeof(buffer));
    }

    if (bytes_received < 0) {
        log_to_error("GET", "/utenti", "506", "Errore nella lettura della risposta dal server JSON");
        perror("Errore nella lettura della risposta dal server JSON");
    }

    log_to_success("GET", "/utenti", "200");

    // Close sockets
    close(json_socket);
    close(client_socket);
}




void get_utente_by_id(int client_socket, int id) {
    char buffer[4096] = {0};
    char endpoint[100];
    snprintf(endpoint, sizeof(endpoint), "/utenti/%d", id);

    // Connect to JSON server
    int json_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (json_socket < 0) {
        log_to_error("GET", (char *) endpoint, "500", "Errore nella creazione del socket");
        perror("Errore nella creazione del socket");
        return; 
    }

    struct sockaddr_in json_server_addr;
    json_server_addr.sin_family = AF_INET;
    json_server_addr.sin_port = htons(JSON_SERVER_PORT);
    // Con inet_pton converto l'indirizzo nella rappresentazione binaria corretta
    if (inet_pton(AF_INET, JSON_SERVER_IP, &json_server_addr.sin_addr) <= 0) {
        log_to_error("GET", (char *) endpoint, "502", "Indirizzo errato / non supportato");
        perror("Indirizzo errato / non supportato");
        close(json_socket);
        return;
    }

    if (connect(json_socket, (struct sockaddr *)&json_server_addr, sizeof(json_server_addr)) < 0) {
        log_to_error("GET", (char *) endpoint, "503", "Connessione al server fallita");
        perror("Connessione al server fallita");
        close(json_socket);
        return;
    }

    // Send request to JSON server
    char request[100];
    sprintf(request, "GET /utenti/%d HTTP/1.1\r\nHost: %s:%d\r\n\r\n", id, JSON_SERVER_IP, JSON_SERVER_PORT);
    if (send(json_socket, request, strlen(request), 0) < 0) {
        log_to_error("GET", (char *) endpoint, "504", "Errore nell'invio della richiesta al server JSON");
        perror("Errore nell'invio della richiesta al server JSON");
        close(json_socket);
        return;
    }

    // Receive response from JSON server and send to client
    ssize_t bytes_received;
    while ((bytes_received = read(json_socket, buffer, sizeof(buffer))) > 0) {
        if (send(client_socket, buffer, bytes_received, 0) < 0) {
            log_to_error("GET", (char *) endpoint, "505", "Errore nell'invio dei dati al client");
            perror("Errore nell'invio dei dati al client");
            close(json_socket);
            return;
        }
    }

    if (bytes_received < 0) {
        log_to_error("GET", (char *) endpoint, "506", "Errore nella lettura della risposta dal server JSON");
        perror("Errore nella lettura della risposta dal server JSON");
    } else {
        // Controllo se l'utente non e' stato trovato nel database
        if (strstr(buffer, "404 Not Found") != NULL) {
            log_to_error("GET", (char *) endpoint, "404", "Utente non trovato nel database");
        } else {
            log_to_success("GET", (char *) endpoint, "200");
        }
    }
    
    // Resetto il buffer
    memset(buffer, 0, sizeof(buffer));

    // Close sockets
    close(json_socket);
    close(client_socket);
}