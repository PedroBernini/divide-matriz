# Divide Matriz

## Objetivo
Este programa utiliza múltiplas threads para dividir uma matriz N x N (N linhas por N colunas) em outras duas matrizes também N x N de tal forma que seja composta por elementos a partir da diagonal principal e acima; e a segunda matriz com elementos abaixo da diagonal principal. O programa deverá ser escrito para o sistema operacional Linux e obrigatoriamente utilizar a biblioteca POSIX Threads.

## Descrição do problema a ser resolvido
Considere  uma  matriz  N x N  (N  linhas  por  N  colunas)  que  contém  valores em  ponto  flutuante,  positivos  ou negativos.  O  programa  deverá  utilizar  múltiplos threads  para  dividir  essa  matriz  em  outras  duas. 

A matriz original deve ser dividida em outras duas matrizes também N x N de tal forma que a primeira matriz seja composta por elementos a partir da diagonal principal e acima; e a segunda matriz com elementos abaixo da diagonal principal. Os dados da matriz original devem vir de um arquivo e as matrizes resultantes devem ser gravadas em arquivos com as extensões diag1 para os dados da primeira matriz e diag2 para os dados da segunda matriz. 
    
## Entradas e saídas de valores para o programa
Entradas: os valores N, T e Arquivo -- respectivamente, as dimensões da matriz (N x N); o número de threads; e o arquivo onde estão os dados -- devem ser informados pelo usuário no início do programa. Para os testes, considere valores grandes (maiores ou iguais a 100) para N.

Saídas: arquivos  com  as  matrizes  diagonal  superior  e  diagonal  inferior.  Os  arquivos  gerados  devem  ter  o mesmo  nome  do  arquivo  original  e  as  extensões diag1  para  a  primeira  matriz  e diag2  para  a  segunda matriz. 
