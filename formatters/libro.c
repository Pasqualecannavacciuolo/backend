#include "libro.h"
// Definizione della variabile keys
const char *keys[] = {"titolo", "autore", "isbn"};

char* libro_to_json(Libro libro) {
    char jsonString[512];
    char tempStr[100];

    // Inizializzazione della stringa JSON
    strcpy(jsonString, "{");

    // Genero il contentuo in formato JSON
    for (unsigned long i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        if(strcmp(keys[i],"titolo") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", keys[i], libro.titolo);
        } else if(strcmp(keys[i],"autore") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", keys[i], libro.autore);
        } else if(strcmp(keys[i],"isbn") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", keys[i], libro.isbn);
        }
        strcat(jsonString, tempStr);
    }

    // Chiusura del JSON
    strcat(jsonString, "}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}