//Este modulo contem as funcoes responsaveis por codificar e decodificar mensagens
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"

#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

int cifrar(int mensagem, int exp_cifragem, int modulo){
	/* Retorna o resultado de m^e mod n, onde:
	e: exp_cifragem;
	n: modulo;
	m: mensagem a ser cifrada (em numeros). */

	int num = 1;

	for(int i = 0; i < exp_cifragem; i++){
		num *= (mensagem % modulo);
		num = num % modulo;
	}
	return num;
}

int decifrar(int mensagem_cifrada, int exp_decifragem, int modulo)
{
	// decifra um caractere de uma mensagem baseado no modulo e no expoente de decifragem.
	int num = 1;

	for(int i = 0; i < exp_decifragem; i++){
		num *= (mensagem_cifrada % modulo);
		num = num % modulo;
	}
	return num;
}

char *codificar(char *mensagem, int modulo, int totiente) {
	/* Transforma a mensagem em um vetor com os respectivos valores ASCII;
	em seguida, concatena esses vetores em uma string. Essa string e cortada de
	tal maneira que cada corte seja sempre menor que o totiente, e então a nova 
	string cortada (sliced) e armazenada no vetor *codificado. Esse vetor e, entao,
	cifrado, e entao concatenado novamente, gerando a mensagem de saida.*/

	int i = 0;
	int *ascii;
	int *codificado;
	char *mensagem_saida;
	int tamanho = strlen(mensagem);
	int exp_cifragem = menor_coprimo(totiente);

	ascii = str_to_ascii(mensagem);

	mensagem_saida = concatenar_vetor(ascii, tamanho, VECTOR_TERMINATOR);
	free(ascii);
	codificado = split_ascii(mensagem_saida, totiente, VECTOR_TERMINATOR);
	for(i = 0; i < tamanho && codificado[i] != VECTOR_TERMINATOR; i++){
		codificado[i] = cifrar(codificado[i], exp_cifragem, modulo);
	}
	codificado[i] = VECTOR_TERMINATOR;
	mensagem_saida = concatenar_vetor(codificado, tamanho, VECTOR_TERMINATOR);
	free(codificado);
	tamanho = strlen(mensagem_saida);
	mensagem_saida[tamanho] = '\0';
	return mensagem_saida;
}

char *decodificar(char *mensagem_codificada, int modulo, int exp_decifragem)
{
	int i = 0;
	char *mensagem_decodificada;
	int *ascii;
	int *decodificado; 
	int tamanho = strlen(mensagem_codificada);

	decodificado = (int*) malloc(sizeof(int) * tamanho + 1);
	printf("Splitting ascii...\n");
	ascii = split_ascii(mensagem_codificada, modulo, VECTOR_TERMINATOR);
	free(ascii);
	for(i = 0; i < tamanho && ascii[i] != VECTOR_TERMINATOR; i++){
		decodificado[i] = decifrar(ascii[i], exp_decifragem, modulo);
	}
	decodificado[i] = VECTOR_TERMINATOR;
	mensagem_decodificada = concatenar_vetor(decodificado, tamanho, VECTOR_TERMINATOR);
	free(decodificado);
	return mensagem_decodificada;
}