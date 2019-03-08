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
    double **matrizOrg;
    double **matrizDiag1;
    double **matrizDiag2;
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

    //Lê um elemento e salva na matriz rotacionada nLeitura vezes
    int j;
    for(j=0;j<argumentos->nLeituras;j++){

        elemento = argumentos->matrizOrg[linha][coluna];

        //Acima ou na diagonal principal
	if(coluna>=linha){
            argumentos->matrizDiag1[linha][coluna] = elemento;
	    argumentos->matrizDiag2[linha][coluna] = 0.00;
	}

	//Abaixo da diagonal principal
	else{
	    argumentos->matrizDiag2[linha][coluna] = elemento;
	    argumentos->matrizDiag1[linha][coluna] = 0.00;
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
