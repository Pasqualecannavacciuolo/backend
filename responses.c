#include "responses.h"

char* send_get_response() {
    char *message = NULL;
    int message_size;
    char message_size_str[20]; // Massimo numero di cifre per la dimensione sia 20

    // Allocazione dinamica del messaggio
    message = (char *)malloc(100 * sizeof(char)); // In base alle esigenze verra' regolata
    if (message == NULL) {
        printf("Errore durante l'allocazione della memoria per il messaggio.\n");
        return NULL;
    }
    strcpy(message, "Hello, World!");
    message_size = strlen(message);

    // Converte l'intero message_size in una stringa
    sprintf(message_size_str, "%d", message_size);

    // Costruisce la stringa base
    char *response = (char *)malloc(200 * sizeof(char)); // Allocazione dinamica della risposta
    if (response == NULL) {
        printf("Errore durante l'allocazione della memoria per la risposta.\n");
        free(message);
        return NULL;
    }
    strcpy(response, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: ");
    strcat(response, message_size_str);
    strcat(response, "\n\n");

    // Concatena la stringa base con il messaggio
    strcat(response, message);

    free(message); // Libera la memoria allocata per il messaggio

    return response;
}