#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    const char **sorted_guesses = malloc(NUM_GUESSES * sizeof(const char *));
    if (!sorted_guesses) return 1;

    for (int i = 0; i < NUM_GUESSES; i++) {
        sorted_guesses[i] = VALID_GUESSES[i];
    }

    qsort(sorted_guesses, NUM_GUESSES, sizeof(const char *), compare);

    FILE *f = fopen("database_novo.c", "w");
    if (!f) {
        free(sorted_guesses);
        return 1;
    }

    fprintf(f, "#include \"database.h\"\n\n");
    fprintf(f, "const char* VALID_GUESSES[] = {\n");

    for (int i = 0; i < NUM_GUESSES; i++) {
        fprintf(f, "    \"%s\",\n", sorted_guesses[i]);
    }

    fprintf(f, "};\n\n");
    fprintf(f, "const int NUM_GUESSES = %d;\n", NUM_GUESSES);

    fclose(f);
    free(sorted_guesses);
    return 0;
}