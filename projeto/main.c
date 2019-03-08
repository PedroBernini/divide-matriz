/**
 * Objetivo: Este programa deve dividir uma matriz em outras duas por meio da diagonal principal
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Sex 08 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(int argc, char *argv[]	){

    //Imprime cabeçalho
    header();

    //Ordem da matriz
    int n;
    char ordem[6];
    strcpy(ordem,argv[1]);
    n = atoi(argv[1]);
    
    //Threads
    int nThreads;
    nThreads = atoi(argv[2]);

    //Arquivos
    char nomeArquivo[30];
    strcpy(nomeArquivo, argv[3]);

    char nomeCompleto[30];
    strcpy(nomeCompleto, argv[3]);
    const char c[2] = ".";
    char *token;
    token = strtok(nomeCompleto, c);

    char arquivoFinal[30];  
    strcpy(arquivoFinal, token);

    printf("\n| MATRIZ ORIGINAL |\n");
    printf("Nome do arquivo: %s\n", nomeArquivo);
    printf("Ordem da matriz: %d\n", n);

    printf("\n--------------------------------------------------------\n");
    printf("Dividindo Matriz com %d Threads...\n", nThreads);
    printf("--------------------------------------------------------\n");

    int i;

    double **matrizDiag1;
    matrizDiag1 = (double **) malloc (n * sizeof (double *));
    for (i = 0; i < n; i++)
        matrizDiag1[i] = (double *) malloc (n * sizeof (double));

    double **matrizDiag2;
    matrizDiag2 = (double **) malloc (n * sizeof (double *));
    for (i = 0; i < n; i++)
        matrizDiag2[i] = (double *) malloc (n * sizeof (double));

    //Cria threads passando argumentos necessários
    int nLeituras = n*n/nThreads;
    int sobra = n*n%nThreads;

    for(i=0; i<nThreads; i++){
	vArgumentos[i].idThread = i + 1;
	vArgumentos[i].ordem = n;
	vArgumentos[i].nThreads = nThreads;
	vArgumentos[i].nLeituras = nLeituras;
	if(i == (nThreads - 1))
	    vArgumentos[i].nLeituras += sobra;
	vArgumentos[i].posicaoInicial = nLeituras*i + 1;
	strcpy(vArgumentos[i].nomeArquivo,nomeArquivo);
	vArgumentos[i].elementoDiag1 = matrizDiag1;
	vArgumentos[i].elementoDiag2 = matrizDiag2;

	pthread_create(&threadID[i], NULL, threadDividirValores, (void *)&vArgumentos[i]);
    }

    //Faz com que a main() não termine antes das outras threads
    for(i=0; i<nThreads; i++)
        pthread_join(threadID[i], NULL);

    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,arquivoFinal);
    strcat(diretorio,".diag1");
    FILE *arquivo1 = fopen(diretorio,"w");

    char diretorio2[100] = "";
    strcat(diretorio2,"../arquivos/matrizes/");
    strcat(diretorio2,arquivoFinal);
    strcat(diretorio2,".diag2");
    FILE *arquivo2 = fopen(diretorio2,"w");

    int j;
    //Matriz com a diagonal principal e acima
    for(i=0;i<n;i++){
        fprintf(arquivo1," ");
	for(j=0;j<n;j++){
	    fprintf(arquivo1, "%lf  ", matrizDiag1[i][j]);
            if(j != (n-1))
		fprintf(arquivo1," ");
        }
	fprintf(arquivo1,"\n");
    }

    //Matriz abaixo da diagonal principal
    for(i=0;i<n;i++){
        fprintf(arquivo2," ");
	for(j=0;j<n;j++){
	    fprintf(arquivo2, "%lf  ", matrizDiag2[i][j]);
            if(j != (n-1))
		fprintf(arquivo2," ");
        }
	fprintf(arquivo2,"\n");
    }

    printf("\nMatriz dividida com sucesso!\n");
    printf("Nome da primeira matriz resultante: %s.diag1\n", arquivoFinal);
    printf("Nome da segunda matriz resultante: %s.diag2\n\n", arquivoFinal);
    
    return 0;
}
