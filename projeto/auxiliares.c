#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/**
 * Função auxiliar que imprime cabeçalho do programa
**/
void header() {
    printf("\n-------------------------------------------------------------\n");
    printf("ESTE PROGRAMA DEVE DIVIDIR UMA MATRIZ EM OUTRAS DUAS MATRIZES\n");
    printf("-------------------------------------------------------------\n");
}

/**
 * Função auxiliar que executa outro programa do projeto
 * para gerar uma matriz em um arquivo
 *
 * @param linhas - número de linhas da matriz
 * @param colunas - número de colunas da matriz
 * @param arquivo - nome do arquivo a ser gravado
 *
 * Observações: programa auxiliar desenvolvido
 * pelo Professor Andre Leon S. Gradvohl, Dr.
**/
void geraMatriz(char linhas[6], char colunas[6], char arquivo[30]) {
    arquivo[strlen(arquivo)-1] = '\0';
    char comando[100] = "";

    strcat(comando,"../plugins/generateRandomMatrixDouble ");
    strcat(comando,linhas);
    strcat(comando,colunas);
    strcat(comando,"../arquivos/matrizes/");
    strcat(comando,arquivo);

    system(comando);
}
