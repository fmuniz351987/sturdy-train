/*Esse modulo contem funcoes associadas a conversao de char[] para 
int[] (e vice-versa) onde os valores do vetor de inteiros equivalem aos valores 
ASCII de cada caractere em char[] */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void menos_um(int *ascii, int tamanho){
	for (int i = 0; i < tamanho; i++){
		ascii[i] = -1;
	}
}

void str_to_ascii(char *mensagem, int *ascii, int tamanho) {
	//transforma a mensagem em um vetor com valores ASCII
	for(int i = 0; i < tamanho; i++){
		ascii[i] = (int)mensagem[i];
	}
}

void ascii_to_str(int *ascii, char *mensagem_saida, int tamanho) {
	//transforma de volta um vetor ASCII em uma mensagem char[]
	for(int i = 0; i < tamanho; i++) {
		mensagem_saida[i] = (char)ascii[i];
	}
	mensagem_saida[tamanho] = '\0';	//garante que a mensagem termine onde deveria
}

int strslice(char *texto, int inicio, int fim) {
	/* modifica slice para ser uma parte da string texto que começa em inicio (inclusivo) 
	e termina em fim (exclusivo) */
	char slice[fim - inicio + 1];
	for(int i = inicio; i < fim; i++){
		slice[i - inicio] = texto[i];
	}
	slice[fim - inicio] = '\0';
	return atoi(slice);
}

void concatenar_vetor(int *vetor, char *texto_saida, int tamanho, int invalido){
	/* transforma uma sequencia de numeros (vetor) em uma string, que é armazenada
	em texto_saida */
	strcpy(texto_saida, "");
	for(int i = 0; i < tamanho; i++){
		if(vetor[i] == invalido) break;
		sprintf(texto_saida, "%s%i", texto_saida, vetor[i]);
	}
}

void split_ascii(char *mensagem, int *ascii, int tamanho, int totiente) {
	int cont = 0;
	int slice;
	int i = 0, j = 0;

	menos_um(ascii, tamanho);
	while(i < tamanho){
		for(j = i + 1; j <= tamanho; j++){
			slice = strslice(mensagem, i, j);
			if(slice >= totiente){
				ascii[cont] = strslice(mensagem, i, j - 1);
				cont++;
				i = j-1;
			} else if (j == tamanho ) {
				ascii[cont] = strslice(mensagem, i, j);
				cont++;
				i = tamanho;
			}
		}
	}
}
