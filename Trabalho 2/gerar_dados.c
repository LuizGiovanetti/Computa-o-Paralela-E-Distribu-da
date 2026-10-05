#include <stdio.h>
#include <stdlib.h>

#define N 1000000

int main(void)
{
    int i;

    FILE *arquivo;

    arquivo = fopen("dados/pontos.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo dados/pontos.txt\n");
        return 1;
    }

    srand(42);

    for (i = 0; i < N; i++)
    {
        double x;
        double y;

        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        fprintf(arquivo, "%.10f %.10f\n", x, y);
    }

    fclose(arquivo);

    printf("============================================\n");
    printf("          GERACAO DOS DADOS\n");
    printf("============================================\n");
    printf("Pontos gerados: %d\n", N);
    printf("Arquivo: dados/pontos.txt\n");
    printf("============================================\n");

    return 0;
}