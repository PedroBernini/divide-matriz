/**
 * Objetivo: Este programa deve dividir uma matriz em outras duas por meio da diagonal principal
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Sex 01 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(){

    //Imprime cabeçalho
    header();

    //Variáveis de tratamento (PARTE 1)
    int potencia;
    int inteiro = 0;
    int valido;
    int i;
    char validador;
    
    /* PARTE 1 - GERAR MATRIZ */
    printf("\n| PARTE 1 - GERANDO MATRIZ ORIGINAL |\n");
    printf("\nPara gerar a matriz, entre com...\n");

	//Trata entrada da ordem da matriz
        inteiro = 0;
        int n;
        char ordem[6];
        do{
            printf("\n\tOrdem da matriz [N]: ");
            fgets(ordem,6,stdin);
	    potencia = strlen(ordem)-1;

            i = 0;
            valido = 1;
            validador = ordem[i];
            do{
                if(!validaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = ordem[i];
            }while(validador!='\n');

            if(valido){
                ordem[i] = ' ';
	        n = inteiro;
            }else{
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
	    }
        }while(!valido);

	//Recebe entrada do arquivo
        char nomeArquivo[30];
        printf("\n\tNome do arquivo: ");
	fgets(nomeArquivo,30,stdin);

	//Gera matriz n*n no arquivo
        printf("\n--------------------------------------------------------\n");
        geraMatriz(ordem, ordem,nomeArquivo);
        printf("--------------------------------------------------------\n");
    /**/

    /* PARTE 2 - ESCOLHER NUMERO DE THREADS */
    printf("\n| PARTE 2 - NUMERO DE THREADS PARA DIVIDIR A MATRIZ |\n");
    printf("\n** O numero de threads deve ser entre 1 e 16 e menor ou igual NxN **\n");

	//Trata entrada de threads
	int nThreads;
	printf("\n\tNumero de threads [T]: ");
	scanf("%d",&nThreads);

	while(nThreads<=0 || nThreads>16 || nThreads>n*n){
	    printf("\tNumero invalido!\n");
	    printf("\tDigite novamente...\n");

	    printf("\n\tNumero de threads (T): ");
	    scanf("%d",&nThreads);
	}

	printf("\n--------------------------------------------------------\n");
        printf("Dividindo Matriz...\n");
	printf("--------------------------------------------------------\n");
    /**/

    /* PARTE 3 - DIVIDIR MATRIZ */

    //Alocando memória para divisão das matrizes
    double **matrizDiag1;
    matrizDiag1 = (double **) malloc (n * sizeof (double *));
    for (int i = 0; i < n; i++)
        matrizDiag1[i] = (double *) malloc (n * sizeof (double));

    double **matrizDiag2;
    matrizDiag2 = (double **) malloc (n * sizeof (double *));
    for (int i = 0; i < n; i++)
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

    /* PARTE 4 - SALVAR AS NOVAS MATRIZES RESULTANTES */
    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,nomeArquivo);
    strcat(diretorio,".diag1");
    FILE *arquivo1 = fopen(diretorio,"w");

    char diretorio2[100] = "";
    strcat(diretorio2,"../arquivos/matrizes/");
    strcat(diretorio2,nomeArquivo);
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
    printf("Nome da matriz original: %s.dat\n", nomeArquivo);
    printf("Nome da primeira matriz resultante: %s.diag1\n", nomeArquivo);
    printf("Nome da segunda matriz resultante: %s.diag2\n\n", nomeArquivo);
    
    return 0;
}
