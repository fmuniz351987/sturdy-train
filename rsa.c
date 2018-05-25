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

void codificar(char *mensagem, char *mensagem_saida, int tamanho_entrada, int modulo, int totiente) {
	int i = 0;
	int ascii[tamanho_entrada];	//armazena temporariamente os valores ascii dos caracteres da mensagem

	resetar_vetor(ascii, tamanho_entrada, VECTOR_TERMINATOR);
	str_to_ascii(mensagem, ascii, tamanho_entrada);
	concatenar_vetor(ascii, mensagem_saida, tamanho_entrada, VECTOR_TERMINATOR);
	resetar_vetor(ascii, tamanho_entrada, VECTOR_TERMINATOR);
	printf("Expoente:%d\n", menor_coprimo(totiente));
	split_ascii(mensagem_saida, ascii, strlen(mensagem_saida), totiente, VECTOR_TERMINATOR);
	printf("Expoente:%d\n", menor_coprimo(totiente));	//MUDOU???
	for(i = 0; i < tamanho_entrada && ascii[i] != VECTOR_TERMINATOR; i++){
		ascii[i] = cifrar(ascii[i], menor_coprimo(totiente), modulo);
	}
	printf("Segunda concatenacao\n");
	concatenar_vetor(ascii, mensagem_saida, tamanho_entrada, VECTOR_TERMINATOR);
}