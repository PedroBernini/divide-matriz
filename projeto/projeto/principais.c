#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Estrutura de argumentos para threads
typedef struct Argumentos{
    int idThread;
    int ordem;
    int nThreads;
    int nLeituras;
    int posicaoInicial;
    char nomeArquivo[30];
    double *elementoDiag1;
    double *elementoDiag2;
}argumentos;

//Variáveis globais do programa
pthread_t threadID[16];
argumentos vArgumentos[16];

/**
 * Função que representa uma thread genérica que deve percorrer
 * o arquivo a partir de um ponto inicial e modificar a matrizes resultantes
 *
 * @param *vArgumentos - ponteiro para uma estrutura de argumentos
**/
void *threadDividirValores(void *vArgumentos){
    argumentos *argumentos = vArgumentos;

    //Abre arquivo da matriz
    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,argumentos->nomeArquivo);
    strcat(diretorio,".dat");
    FILE *arquivo = fopen(diretorio,"r");

    //Calcula índice linha segundo posição inicial
    int linha;
    if(argumentos->posicaoInicial%argumentos->ordem > 0 || argumentos->posicaoInicial/argumentos->ordem == 0)
        linha = argumentos->posicaoInicial/argumentos->ordem;
    else
        linha = argumentos->posicaoInicial/argumentos->ordem - 1;

    //Calcula índice coluna segundo posição inicial
    int coluna;
    if(argumentos->posicaoInicial-argumentos->ordem < 0)
        coluna = (argumentos->posicaoInicial-argumentos->ordem)%argumentos->ordem + argumentos->ordem;
    else if((argumentos->posicaoInicial-argumentos->ordem)%argumentos->ordem == 0)
        coluna = argumentos->ordem;
    else
	coluna = (argumentos->posicaoInicial-argumentos->ordem)%argumentos->ordem;
    coluna--;

    double elemento;

    //Percorre matriz até a posição inicial 
    register int i;
    argumentos->posicaoInicial--;
    for(i=1;i<=argumentos->posicaoInicial;i++){
        fscanf(arquivo,"%lf",&elemento);
    }

    //Lê um elemento e salva na matriz rotacionada nLeitura vezes
    int j;
    for(j=0;j<argumentos->nLeituras;j++){

        fscanf(arquivo,"%lf",&elemento);

        //Acima ou na diagonal principal
	if(coluna>=linha){
            argumentos->elementoDiag1[linha * argumentos->ordem + coluna] = elemento;
	}

	//Abaixo da diagonal principal
	else{
	    argumentos->elementoDiag2[linha * argumentos->ordem + coluna] = elemento;
	}

	if(coluna == argumentos->ordem-1){
	    coluna = 0;
	    linha++;
	}else
	    coluna++;
    }

    //Finaliza thread
    pthread_exit(NULL);
}
