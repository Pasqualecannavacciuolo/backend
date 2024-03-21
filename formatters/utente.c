#include "utente.h"

// Definizione della variabile utente_keys
const char *utente_keys[] = {"id", "nome", "cognome", "prestiti"};
const char *register_utente_keys[] = {"id", "nome", "cognome", "nome_utente", "data_nascita", "codice_fiscale", "email", "password", "tipo_utente"};

char *utente_to_json(Utente utente)
{
    char jsonString[2048];
    char tempStr[512];

    // Inizializzazione della stringa JSON
    strcpy(jsonString, "{");

    // Genero il contentuo in formato JSON
    for (unsigned long i = 0; i < sizeof(utente_keys) / sizeof(utente_keys[0]); i++)
    {
        if (strcmp(utente_keys[i], "id") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%d\", ", utente_keys[i], utente.id);
        }
        else if (strcmp(utente_keys[i], "nome") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", utente_keys[i], utente.nome);
        }
        else if (strcmp(utente_keys[i], "cognome") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", utente_keys[i], utente.cognome);
        }
        else if (strcmp(utente_keys[i], "prestiti") == 0)
        {
            // Formatta i prestiti in JSON
            sprintf(tempStr, "\"%s\": [", utente_keys[i]);
            strcat(jsonString, tempStr);

            for (int j = 0; j < MAX_PRESTITI; j++)
            {
                sprintf(tempStr, "{\"id_libro\": \"%s\", \"data_inizio\": \"%s\", \"data_scadenza\": \"%s\"}, ",
                        utente.prestiti[j].id_libro, utente.prestiti[j].data_inizio, utente.prestiti[j].data_scadenza);
                strcat(jsonString, tempStr);
            }
            strcat(jsonString, "], ");
        }
        strcat(jsonString, tempStr);
    }

    // Chiusura del JSON
    strcat(jsonString, "}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}

char *register_utente_to_json(Register utente)
{
    char jsonString[2048];
    char tempStr[512];

    // Inizializzazione della stringa JSON
    strcpy(jsonString, "{");

    // Genero il contentuo in formato JSON
    for (unsigned long i = 0; i < sizeof(register_utente_keys) / sizeof(register_utente_keys[0]); i++)
    {
        if (strcmp(register_utente_keys[i], "id") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%d\", ", register_utente_keys[i], utente.id);
        }
        else if (strcmp(register_utente_keys[i], "nome") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.nome);
        }
        else if (strcmp(register_utente_keys[i], "cognome") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.cognome);
        }
        else if (strcmp(register_utente_keys[i], "nome_utente") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.nome_utente);
        }
        else if (strcmp(register_utente_keys[i], "data_nascita") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.data_nascita);
        }
        else if (strcmp(register_utente_keys[i], "codice_fiscale") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.codice_fiscale);
        }
        else if (strcmp(register_utente_keys[i], "email") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.email);
        }
        else if (strcmp(register_utente_keys[i], "password") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.password);
        }
        else if (strcmp(register_utente_keys[i], "tipo_utente") == 0)
        {
            sprintf(tempStr, "\"%s\": \"%s\", ", register_utente_keys[i], utente.tipo_utente);
        }
        strcat(jsonString, tempStr);
    }

    // Chiusura del JSON
    strcat(jsonString, "}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}