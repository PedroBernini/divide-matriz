/**
 * Objetivo: Este programa deve dividir uma matriz em outras duas por meio da diagonal principal
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Sex 11 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "principais.c"
#include "auxiliares.c"

int main(int argc, char *argv[]	){

    //Medir tempo de todo o programa
    clock_t tempos[4];
    tempos[0] = clock();
	
    if(argc != 4){
	printf("\nArgumentos invalidos!\n");
	printf("Tente: ./<Nome do Executavel> <Ordem da matriz> <Numero de Threads> <Nome do arquivo>\n\n");
	return 0;
    }

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
    int j;
    double elemento;

    double **matrizOrg;
    matrizOrg = (double **) malloc (n * sizeof (double *));
    for (i = 0; i < n; i++)
        matrizOrg[i] = (double *) malloc (n * sizeof (double));

    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,nomeArquivo);
    FILE *arquivo = fopen(diretorio,"r");

    if (arquivo == NULL) {
	printf("\nO arquivo '%s' não existe na pasta '../arquivos/matrizes/'\n", nomeArquivo);
	printf("Finalizando programa.\n\n");
	return 0;
    }


    for(i=0;i<n;i++){
	for(j=0;j<n;j++){
            fscanf(arquivo,"%lf",&elemento);
            matrizOrg[i][j] = elemento;
        }
    }

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

    //Medir tempo de execução da divisao da matriz
    tempos[2] = clock();

    for(i=0; i<nThreads; i++){
	vArgumentos[i].idThread = i + 1;
	vArgumentos[i].ordem = n;
	vArgumentos[i].nThreads = nThreads;
	vArgumentos[i].nLeituras = nLeituras;
	if(i == (nThreads - 1))
	    vArgumentos[i].nLeituras += sobra;
	vArgumentos[i].posicaoInicial = nLeituras*i + 1;
	vArgumentos[i].matrizOrg = matrizOrg;
	vArgumentos[i].matrizDiag1 = matrizDiag1;
	vArgumentos[i].matrizDiag2 = matrizDiag2;

	pthread_create(&threadID[i], NULL, threadDividirValores, (void *)&vArgumentos[i]);
    }

    //Faz com que a main() não termine antes das outras threads
    for(i=0; i<nThreads; i++)
        pthread_join(threadID[i], NULL);
    
    tempos[3] = clock();
    double TempoDivisao = (tempos[3] - tempos[2]) * 1000.0 / CLOCKS_PER_SEC;

    strcpy(diretorio,"");
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,arquivoFinal);
    strcat(diretorio,".diag1");
    FILE *arquivo1 = fopen(diretorio,"w");

    strcpy(diretorio,"");
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,arquivoFinal);
    strcat(diretorio,".diag2");
    FILE *arquivo2 = fopen(diretorio,"w");

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

    tempos[1] = clock();
    double TempoPrograma = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;

    printf("\nMatriz dividida com sucesso!\n");
    printf("Nome da primeira matriz resultante: %s.diag1\n", arquivoFinal);
    printf("Nome da segunda matriz resultante: %s.diag2\n\n", arquivoFinal);
    printf("Tempo gasto para dividir a matriz -> %g ms.\n", TempoDivisao);
    printf("Tempo total do programa -> %g ms.\n\n", TempoPrograma);
    
    return 0;
}
