#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *in = fopen("grafo_result.txt", "r");
    if (!in) {
        printf("Erro: Nao foi possivel abrir grafo_result.txt\n");
        return 1;
    }

    FILE *out = fopen("grafo.h", "w");
    if (!out) {
        printf("Erro: Nao foi possivel criar grafo.h\n");
        fclose(in);
        return 1;
    }

    int rows = 0;
    int cols = 0;
    int current_cols = 0;
    char c;

    // Passo 1: Descobrir as dimensões da matriz
    // Conta '0's e '1's até achar um '\n' para definir a quantidade de colunas
    while ((c = fgetc(in)) != EOF) {
        if (c == '0' || c == '1') {
            current_cols++;
        } else if (c == '\n') {
            if (current_cols > 0) {
                cols = current_cols;
                rows++;
                current_cols = 0;
            }
        }
    }
    // Trata o caso do arquivo não terminar com \n na última linha
    if (current_cols > 0) {
        cols = current_cols;
        rows++;
    }

    // Volta o ponteiro para o início do arquivo para a segunda leitura
    rewind(in);

    // Passo 2: Escrever o arquivo .h
    fprintf(out, "#ifndef GRAFO_H\n");
    fprintf(out, "#define GRAFO_H\n\n");
    
    fprintf(out, "// Dimensoes do grafo autogeradas\n");
    fprintf(out, "#define GRAFO_ROWS %d\n", rows);
    fprintf(out, "#define GRAFO_COLS %d\n\n", cols);
    
    fprintf(out, "const int GRAFO[%d][%d] = {\n", rows, cols);

    int val;
    for (int i = 0; i < rows; i++) {
        fprintf(out, "    {");
        for (int j = 0; j < cols; j++) {
            // fscanf com %d ignora automaticamente os espaços e quebras de linha
            if (fscanf(in, "%d", &val) == 1) {
                fprintf(out, "%d", val);
                if (j < cols - 1) {
                    fprintf(out, ", ");
                }
            }
        }
        fprintf(out, "}");
        if (i < rows - 1) {
            fprintf(out, ",");
        }
        fprintf(out, "\n");
    }

    fprintf(out, "};\n\n");
    fprintf(out, "#endif // GRAFO_H\n");

    printf("Sucesso! 'grafo.h' gerado com uma matriz %d x %d.\n", rows, cols);

    fclose(in);
    fclose(out);

    return 0;
}