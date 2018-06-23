//Este modulo contem as funcoes responsaveis por codificar e decodificar mensagens

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"

#define VECTOR_TERMINATOR -1

char *padding(int numero, int digitos) {
	// acrescenta zeros à esquerda de numero até que ele tenha o número de dígitos fornecido e retorna como char*
	int digitos_faltantes = digitos - ndigitos(numero);
	char *numero_preenchido, *zeros;

	numero_preenchido = (char*) malloc(digitos * sizeof(char));
	zeros = (char*) malloc((digitos_faltantes + 1) * sizeof(char));

	sprintf(numero_preenchido, "%d", numero);
	for(int i = 0; i < digitos_faltantes; i++){
		zeros[i] = '0';
	}
	zeros[digitos_faltantes] = '\0';

	sprintf(numero_preenchido, "%s%d", zeros, numero);
	free(zeros);
	return numero_preenchido;
}

char *pad_sequence(int *vetor, int digitos){
	// converte um vetor em uma sequencia de numeros em string com padding ("estufada" com zeros à esquerda)
	int i;
	int tamanho = tamanho_vetor(vetor);
	char *padded_sequence = (char*) malloc((tamanho * digitos + 1) * sizeof(char));
	char *padded_number = (char*) malloc(digitos * sizeof(char));

	//inicializando a string
	padded_number = padding(vetor[0], digitos);
	sprintf(padded_sequence, "%s", padded_number);
	free(padded_number);

	//colocando os elementos restantes
	for(i = 1; i < tamanho; i++){
		padded_number = padding(vetor[i], digitos);
		sprintf(padded_sequence, "%s%s", padded_sequence, padded_number);
		free(padded_number);		
	}
	padded_sequence[tamanho * digitos + 1] = '\0';
	return padded_sequence;
}

int cifrar(int mensagem, int expoente, int modulo){
	/* Retorna o resultado de m^e mod n, onde:
	e: expoente;
	n: modulo;
	m: mensagem a ser cifrada (em numeros). */

	long long int num = 1;

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

	if(para_ascii){
		ascii = str_to_ascii(mensagem);
		mensagem_temp = concatenar_vetor(ascii);
		free(ascii);
		ascii = quebrar_em_blocos(mensagem_temp, max_split);
	} else {
		ascii = quebrar_em_blocos(mensagem, max_split);
	}
	return ascii;
}

void codificar(int *numeros, int modulo, int expoente_cifragem) {
	// Cifra ou decifra vários termos de um vetor usando o modulo e o expoente fornecido.
	int i = 0;
	int tamanho = 0;

	for(i = 0; numeros[i] != VECTOR_TERMINATOR; i++){
		numeros[i] = cifrar(numeros[i], expoente_cifragem, modulo);
		tamanho++;
	}
}
