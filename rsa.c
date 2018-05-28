//Este modulo contem as funcoes responsaveis por codificar e decodificar mensagens
#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"

#define MAX_STRING_SIZE 100
#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

long int cifrar(int mensagem, int exp_cifragem, int modulo){
	long int num = 1;
	for(int i = 0; i < exp_cifragem; i++){
		num *= (mensagem % modulo);
		num = num % modulo;
	}
	return num;
}

char *codificar(char *mensagem, int modulo, int totiente) {
	int i = 0;
	//armazena temporariamente os valores ascii dos caracteres da mensagem
	int *ascii;
	int *codificado;
	char *mensagem_saida;
	int tamanho = strlen(mensagem);

	ascii = str_to_ascii(mensagem);

	mensagem_saida = concatenar_vetor(ascii, tamanho, VECTOR_TERMINATOR);
	free(ascii);
	codificado = split_ascii(mensagem_saida, totiente, VECTOR_TERMINATOR);
	printf("Entrada:%s\nTotiente:%d\nModulo:%d\nExpoente:%d\n", mensagem, totiente, 
	       modulo, menor_coprimo(totiente));
	for(i = 0; i < tamanho && codificado[i] != VECTOR_TERMINATOR; i++){
		codificado[i] = cifrar(codificado[i], menor_coprimo(totiente), modulo);
		printf("%d\n", codificado[i]);
	}
	codificado[i] = -1;
	// printf("Segunda concatenacao\n");
	mensagem_saida = concatenar_vetor(codificado, tamanho, VECTOR_TERMINATOR);
	free(codificado);
	return mensagem_saida;
}