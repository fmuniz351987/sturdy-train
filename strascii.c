/*Esse modulo contem funcoes associadas a conversao de char[] para 
int[] (e vice-versa) onde os valores do vetor de inteiros equivalem aos valores 
ASCII de cada caractere em char[] */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "basemath.h"

#define VECTOR_TERMINATOR -1

int tamanho_vetor_terminado(int *vetor, int vector_terminator)
{
	int i = 0;
	while(vetor[i] != vector_terminator){
		i++;
	}
	return i;
}

int caractere_imprimivel(int caractere)
{
	//retorna 1 se o caractere fornecido for imprimivel em ascii ou 0 caso contrario
	return (caractere <= 255) && (caractere >= 32);
}

int max_vetor_positivos(int *vetor, int tamanho){
	//retorna o maior valor para um vetor de inteiros positivos
	int max = 0;
	for(int i = 0; i < tamanho; i++){
		if(vetor[i] > max) max = vetor[i];
	}
	return max; 
}

void imprimir_vetor(int *vetor, int tamanho){
	//imprime um vetor de inteiros para propósitos de debugging
	for(int i = 0; vetor[i] != VECTOR_TERMINATOR; i++){
		printf("%d ", vetor[i]);
	}
	printf("\n");
}

int *str_to_ascii(char *mensagem) {
	//transforma a mensagem em um vetor com valores ASCII
	int tamanho = strlen(mensagem);
	int *ascii = (int*) malloc(tamanho * sizeof(int));
	for(int i = 0; i < tamanho; i++){
		ascii[i] = (int) mensagem[i];
	}
	return ascii;
}

char *ascii_to_str(int *ascii, int tamanho) {
	//transforma de volta um vetor ASCII em uma mensagem char[]
	int i;
	char *mensagem_saida = (char*) malloc((tamanho + 1)* sizeof(char));
	for(i = 0; ascii[i] != VECTOR_TERMINATOR; i++) {
		mensagem_saida[i] = (char)ascii[i];
		// if(!caractere_imprimivel(ascii[i])) printf("Erro! %d nao e imprimivel.\n", ascii[i]);
	}
	mensagem_saida[i] = '\0';	//garante que a mensagem termine onde deveria
	return mensagem_saida;
}

int strslice(char *texto, int inicio, int fim) {
	/* modifica slice para ser uma parte da string texto que começa em inicio (inclusivo) 
	e termina em fim (exclusivo) */
	char *slice = malloc((fim - inicio + 1) * sizeof(char));
	int slice_value;
	if(fim > strlen(texto)) fim = strlen(texto);	//garante que o slice nao extrapola o fim da string
	for(int i = inicio; i < fim; i++){
		slice[i - inicio] = texto[i];
	}
	slice[fim - inicio] = '\0';
	slice_value = atoi(slice);
	free(slice);
	return slice_value;
}

char *concatenar_vetor(int *vetor, int tamanho, int invalido){
	/* transforma uma sequencia de numeros (vetor) em uma string, que é armazenada
	em texto_saida */
	char *texto_saida = (char*) malloc(tamanho * ndigitos(max_vetor_positivos(vetor, tamanho) + 2)
			 * sizeof(char));
	texto_saida[0] = '\0';
	for(int i = 0; i < tamanho && vetor[i] != invalido; i++){
		sprintf(texto_saida, "%s%i", texto_saida, vetor[i]);
	}
	return texto_saida;
}

int *split_ascii(char *mensagem, int maximo, int vector_terminator) {
	/* divide uma string numerica em varios inteiros menores que o parametro
	fornencido para o maximo, e depois retorna um array com esses inteiros. */
	int tamanho = strlen(mensagem);
	int *ascii = (int*) malloc((tamanho) * sizeof(int));
	int cont = 0;
	int slice;
	int i = 0, j = 0;
	int digitos = ndigitos(maximo);

	while(i < tamanho){
		j = i + digitos;	//final do slice
		if(mensagem[i] == '0') {
			ascii[cont] = 0;
			cont++;
			i++;
			continue;
		}
		slice = strslice(mensagem, i, j);
		if(slice < maximo){
			ascii[cont] = slice;
			cont ++;
			i = j;
			continue;
		} else {
			slice = strslice(mensagem, i, j - 1);
			ascii[cont] = slice;
			cont ++;
			i = j - 1;
			continue;
		}
	}
	ascii[cont] = vector_terminator;
	return ascii;
}
