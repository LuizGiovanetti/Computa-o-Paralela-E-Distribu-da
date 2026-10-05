#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define K 4
#define ITERACOES 20
#define REPETICOES 3


int main(void)
{
    int i, k, iteracao, r;

    static double pontos[N][2];
    static double centroides[K][2];
    static int grupo[N];

    double inicio;
    double fim;
    double tempo;
    double tempos[REPETICOES];
    double media;

    FILE *arquivo;

    arquivo = fopen("dados/pontos.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo dados/pontos.txt\n");
        return 1;
    }

    for (i = 0; i < N; i++)
    {
        fscanf(arquivo, "%lf %lf",
               &pontos[i][0],
               &pontos[i][1]);
    }

    fclose(arquivo);

    printf("============================================\n");
    printf("          K-MEANS - SERIAL\n");
    printf("============================================\n");

    for (r = 0; r < REPETICOES; r++)
    {
        for (k = 0; k < K; k++)
        {
            centroides[k][0] = pontos[k][0];
            centroides[k][1] = pontos[k][1];
        }

        inicio = omp_get_wtime();

        for (iteracao = 0; iteracao < ITERACOES; iteracao++)
        {
            for (i = 0; i < N; i++)
            {
                double menor_distancia = 999999999.0;
                int melhor_grupo = 0;

                for (k = 0; k < K; k++)
                {
                    double dx;
                    double dy;
                    double distancia;

                    dx = pontos[i][0] - centroides[k][0];
                    dy = pontos[i][1] - centroides[k][1];

                    distancia = dx * dx + dy * dy;

                    if (distancia < menor_distancia)
                    {
                        menor_distancia = distancia;
                        melhor_grupo = k;
                    }
                }

                grupo[i] = melhor_grupo;
            }
            {
                double soma_x[K] = {0};
                double soma_y[K] = {0};
                int quantidade[K] = {0};

                for (i = 0; i < N; i++)
                {
                    int g = grupo[i];

                    soma_x[g] += pontos[i][0];
                    soma_y[g] += pontos[i][1];

                    quantidade[g]++;
                }

                for (k = 0; k < K; k++)
                {
                    if (quantidade[k] > 0)
                    {
                        centroides[k][0] =
                            soma_x[k] / quantidade[k];

                        centroides[k][1] =
                            soma_y[k] / quantidade[k];
                    }
                }
            }
        }
        fim = omp_get_wtime();

        tempo = fim - inicio;
        tempos[r] = tempo;

        printf("Repeticao %d: %.6f s\n", r + 1, tempo);
    }
    media = (tempos[0] + tempos[1] + tempos[2]) / 3.0;

    printf("--------------------------------------------\n");
    printf("Media:    %.6f s\n", media);
    printf("============================================\n");

    FILE *fp = fopen("resultados_serial.txt", "w");

    if (fp == NULL)
    {
        printf("Erro ao abrir resultados_serial.txt\n");
        return 1;
    }

    fprintf(fp, "# K-Means - tempo serial de referencia\n");
    fprintf(fp, "tempo_serial\n");
    fprintf(fp, "%.6f\n", media);

    fclose(fp);

    printf("\nArquivo 'resultados_serial.txt' criado.\n");

    return 0;
}