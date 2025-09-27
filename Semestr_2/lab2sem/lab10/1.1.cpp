#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

int compareStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char words[MAX_WORDS][MAX_WORD_LENGTH];
    int wordCount = 0;

    char line[MAX_WORD_LENGTH];
    while (fgets(line, sizeof(line), inputFile) != NULL) {
        char *token = strtok(line, " ");
        while (token != NULL) {
            strcpy(words[wordCount], token);
            wordCount++;
            token = strtok(NULL, " \n");
        }
    }

    qsort(words, wordCount, sizeof(char ), compareStrings);


    for (int i = 0; i < wordCount; i++) {
        fprintf(outputFile, "%s\n", words[i]);
        printf("%s\n", words[i]);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
