#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 100

void eofCheck(FILE *file) {
    if(feof(file)) {
        fprintf(stderr, "File ended unexpectedly early");
        exit(64);
    }
}


char *parseFeald(FILE *file, char *fealdString, int chars) {
    eofCheck(file);
    char line[MAX_LINE_LENGTH];
    fgets(line, MAX_LINE_LENGTH, file);
    if(memcmp(line, fealdString, chars)) {
        fprintf(stderr, "Line had unexpected or malformed keyword");
        exit(64);
    } else {
        char *string = malloc(MAX_LINE_LENGTH * sizeof(char));
        strcpy(string, &line[chars]);
        return string;
    }
}


void startParsing(const char *projectPath) {
    char dataFilePath[50];
    sprintf(dataFilePath, "%s/data.txt", projectPath);
    FILE *dataFile = fopen(dataFilePath, "r");
    if(dataFile == NULL) {
        fprintf(stderr, "algomusic failed to open data file\n");
        exit(64);
    }
    printf("starting to parse data.txt\n");
    char line[MAX_LINE_LENGTH];

    char *artistName = parseFeald(dataFile, "Artist: ", 8);
    char *lastUpdated = parseFeald(dataFile, "Last updated: ", 14);
    printf("artist parsed as: %s", artistName);
    printf("last updated parsed as: %s", lastUpdated);

    eofCheck(dataFile);
    fgets(line, MAX_LINE_LENGTH, dataFile);
    if(memcmp(line, "Sequances:", 10)) {
        fprintf(stderr, "no Sequances line found in data file");
        exit(64);
    }
    printf("Sequances:\n");
    while (1) {
        eofCheck(dataFile);
        fgets(line, MAX_LINE_LENGTH, dataFile);
        if(memcmp(line, "end\n", 4) == 0) break;
        printf("%s", line);
    }

    eofCheck(dataFile);
    fgets(line, MAX_LINE_LENGTH, dataFile);
    printf("Algorithms:\n");
    if(memcmp(line, "Algorithms:\n", 11)) {
        fprintf(stderr, "no Sequances line found in data file");
        exit(64);
    }
    while (1) {
        eofCheck(dataFile);
        fgets(line, MAX_LINE_LENGTH, dataFile);
        if(memcmp(line, "end\n", 4) == 0) break;
        printf("%s", line);
    }
    fclose(dataFile);
    printf("parsing of data.txt done\n");
}
