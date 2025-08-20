#ifndef MYLIB_JSON_H
#define MYLIB_JSON_H

#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Tipo abstrato
typedef cJSON* ArrayJSON;
typedef cJSON* ObjectJSON;

// Lê um JSON de arquivo e retorna um array (cria novo se não existir)
static inline ArrayJSON jsonFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    ArrayJSON array = NULL;

    if (fp) {
        fseek(fp, 0, SEEK_END);
        long size = ftell(fp);
        rewind(fp);

        char *buffer = malloc(size + 1);
        fread(buffer, 1, size, fp);
        buffer[size] = '\0';
        fclose(fp);

        array = cJSON_Parse(buffer);
        free(buffer);

        if (!array || !cJSON_IsArray(array)) {
            if (array) cJSON_Delete(array);
            array = cJSON_CreateArray();
        }
    } else {
        array = cJSON_CreateArray();
    }

    return array;
}

// Adiciona um objeto ao array
static inline void jsonAddObject(ArrayJSON array, ObjectJSON obj) {
    if (array && obj) cJSON_AddItemToArray(array, obj);
}

// Salva o array JSON de volta no arquivo
static inline void jsonSaveToFile(ArrayJSON array, const char *filename) {
    if (!array) return;
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }
    char *printed = cJSON_Print(array);
    if (printed) {
        fprintf(fp, "%s\n", printed);
        free(printed);
    }
    fclose(fp);
}

// Cria um objeto JSON de forma agnóstica
// Uso: jsonCreateObject(6, "nome", "Alice", "idade", 30, "cidade", "SP")
static inline ObjectJSON jsonCreateObject(int nPairs, ...) {
    ObjectJSON obj = cJSON_CreateObject();
    va_list args;
    va_start(args, nPairs);

    for (int i = 0; i < nPairs; i++) {
        const char *key = va_arg(args, const char*);
        int type = va_arg(args, int); // 0 = int, 1 = double, 2 = string, 3 = bool
        switch(type) {
            case 0: {
                int value = va_arg(args, int);
                cJSON_AddNumberToObject(obj, key, value);
                break;
            }
            case 1: {
                double value = va_arg(args, double);
                cJSON_AddNumberToObject(obj, key, value);
                break;
            }
            case 2: {
                const char *value = va_arg(args, const char*);
                cJSON_AddStringToObject(obj, key, value);
                break;
            }
            case 3: {
                int value = va_arg(args, int); // bool como int
                cJSON_AddBoolToObject(obj, key, value);
                break;
            }
            default:
                break;
        }
    }

    va_end(args);
    return obj;
}

// Libera memória do array
static inline void jsonFree(ArrayJSON array) {
    if (array) cJSON_Delete(array);
}

#endif // MYLIB_JSON_H
