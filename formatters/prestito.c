#include "prestito.h"

// Definizione della variabile prestito_keys
const char *prestito_keys[] = {"id_utente", "id_libro", "data_inizio", "data_scadenza"};

char *prestito_to_json(Prestito prestito)
{
    char jsonString[2048];
    char tempStr[512];

    // Inizializzazione della stringa JSON
    strcpy(jsonString, "{");

    // Genero il contentuo in formato JSON
    for (unsigned long i = 0; i < sizeof(prestito_keys) / sizeof(prestito_keys[0]); i++)
    {
        if (strcmp(prestito_keys[i], "id_utente") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%d\", ", prestito_keys[i], prestito.id_utente);
        }
        else if (strcmp(prestito_keys[i], "id_libro") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", prestito_keys[i], prestito.id_libro);
        }
        else if (strcmp(prestito_keys[i], "data_inizio") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", prestito_keys[i], prestito.data_inizio);
        }
        else if (strcmp(prestito_keys[i], "data_scadenza") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", prestito_keys[i], prestito.data_scadenza);
        }
        strcat(jsonString, tempStr);
    }

    // Chiusura del JSON
    strcat(jsonString, "}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}