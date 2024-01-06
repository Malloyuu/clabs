#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 512
#define MAX_ENTITIES 50
#define MAX_ENTITY_LENGTH 50

void sortEntities(char entities[][MAX_ENTITY_LENGTH], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(entities[j], entities[j + 1]) > 0) {
                char temp[MAX_ENTITY_LENGTH];
                strcpy(temp, entities[j]);
                strcpy(entities[j], entities[j + 1]);
                strcpy(entities[j + 1], temp);
            }
        }
    }
}

void printSortedEntities(char entities[][MAX_ENTITY_LENGTH], int n) {
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%s", entities[i]);
    }
    printf(";\n");
}


void extractAndSortEntities(const char *str) {
    char entities[MAX_ENTITIES][MAX_ENTITY_LENGTH];
    char category[MAX_ENTITY_LENGTH];
    int entityCount = 0;
    int entityIndex = 0;
    int categoryIndex = 0;
    bool inEntity = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ':') {
            category[categoryIndex] = '\0';
            inEntity = true;
            entityIndex = 0;
            entityCount = 0;
        } else if (str[i] == ',' || str[i] == ';') {
            if (entityIndex != 0) {
                entities[entityCount][entityIndex] = '\0';
                entityCount++;
            }
            entityIndex = 0;
            if (str[i] == ';') {
                sortEntities(entities, entityCount);
                printf("%s: ", category);
                printSortedEntities(entities, entityCount);
                inEntity = false;
                categoryIndex = 0;
            }
        } else if (inEntity) {
            if (str[i] != ' ') {
                entities[entityCount][entityIndex++] = str[i];
            }
        } else {
            category[categoryIndex++] = str[i];
        }
    }
}




bool isValidFormat(const char *str) {
    bool hasColon = false;
    bool hasSemicolon = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ':') {
            hasColon = true;
        }
        if (str[i] == ';') {
            hasSemicolon = true;
        }
    }

    return hasColon && hasSemicolon;
}

void readLine(char *buffer) {
    int ch, i = 0;
    while ((ch = getchar()) != '\n' && i < MAX_LENGTH - 1) {
        buffer[i++] = ch;
    }
    buffer[i] = '\0';
}


void processInput(char *input) {
    if (isValidFormat(input)) {
        extractAndSortEntities(input);
    } else {
        printf("The string does not match the format.\n");
    }
}

int main() {
    char input[MAX_LENGTH];
    printf("Enter a sentence: ");
    readLine(input);
    processInput(input);
    return 0;
}
