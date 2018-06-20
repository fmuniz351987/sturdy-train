//Este modulo contem as funcoes responsaveis por codificar e decodificar mensagens

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"

#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

char *padding(int numero, int digitos) {
	// acrescenta zeros à esquerda de numero até que ele tenha o número de dígitos fornecido e retorna como char*
	int digitos_faltantes = digitos - ndigitos(numero);
	char *numero_preenchido, *zeros;

	numero_preenchido = (char*) malloc(digitos * sizeof(char));
	zeros = (char*) malloc((digitos_faltantes + 1) * sizeof(char));

	sprintf(numero_preenchido, "%d", numero);
	// printf("%s\n", numero_preenchido);
	for(int i = 0; i < digitos_faltantes; i++){
		zeros[i] = '0';
	}
	zeros[digitos_faltantes] = '\0';
	// printf("%s\n", zeros);
	sprintf(numero_preenchido, "%s%d", zeros, numero);
	free(zeros);
	printf("%s\n", numero_preenchido);
	return numero_preenchido;
}

int cifrar(int mensagem, int expoente, int modulo){
	/* Retorna o resultado de m^e mod n, onde:
	e: expoente;
	n: modulo;
	m: mensagem a ser cifrada (em numeros). */

	int num = 1;

	for(int i = 0; i < expoente; i++){
		num *= mensagem;
		num %= modulo;
	}
	return num;
}

int *converter_para_ascii_e_dividir(char *mensagem, int max_split, int para_ascii){
	// retorna um vetor com uma string dividida em blocos menores que max_split
	char *mensagem_temp;
	int *ascii;
	int tamanho = strlen(mensagem);

	if(para_ascii){
		ascii = str_to_ascii(mensagem);
		mensagem_temp = concatenar_vetor(ascii, tamanho, VECTOR_TERMINATOR);
		free(ascii);
		ascii = split_ascii(mensagem_temp, max_split, VECTOR_TERMINATOR);
	} else {
		ascii = split_ascii(mensagem, max_split, VECTOR_TERMINATOR);
	}
	return ascii;
}

char *codificar(int *ascii, int modulo, int expoente_cifragem) {
	/* Transforma a mensagem em um vetor com os respectivos valores ASCII;
	em seguida, concatena esses vetores em uma string. Essa string e cortada de
	tal maneira que cada corte seja sempre menor que o totiente, e então a nova 
	string cortada (sliced) e armazenada no vetor *codificado. Esse vetor e, entao,
	cifrado, e entao concatenado novamente, gerando a mensagem de saida.*/

	int i = 0;
	char *mensagem_saida;
	int tamanho = 0;

	for(i = 0; ascii[i] != VECTOR_TERMINATOR; i++){
		ascii[i] = cifrar(ascii[i], expoente_cifragem, modulo);
		tamanho++;
	}
	ascii[i] = VECTOR_TERMINATOR;
	mensagem_saida = concatenar_vetor(ascii, tamanho, VECTOR_TERMINATOR);
	tamanho = strlen(mensagem_saida);
	mensagem_saida[tamanho] = '\0';
	return mensagem_saida;
}
