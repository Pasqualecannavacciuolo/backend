#include "libro.h"
// Definizione della variabile libro_keys
const char *libro_keys[] = {"titolo", "autore", "isbn"};

char* libro_to_json(Libro libro) {
    char jsonString[2048];
    char tempStr[512];

    // Inizializzazione della stringa JSON
    strcpy(jsonString, "{");

    // Genero il contentuo in formato JSON
    for (unsigned long i = 0; i < sizeof(libro_keys) / sizeof(libro_keys[0]); i++) {
        if(strcmp(libro_keys[i],"titolo") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", libro_keys[i], libro.titolo);
        } else if(strcmp(libro_keys[i],"autore") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", libro_keys[i], libro.autore);
        } else if(strcmp(libro_keys[i],"isbn") == 0) {
            sprintf(tempStr, "\"%s\": \"%s\", ", libro_keys[i], libro.isbn);
        }
        strcat(jsonString, tempStr);
    }

    // Chiusura del JSON
    strcat(jsonString, "}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}