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

void codificar(char *mensagem, char *mensagem_saida, int tamanho, int modulo, int totiente) {
	int i = 0;
	int ascii[tamanho];	//armazena temporariamente os valores ascii dos caracteres da mensagem

	for(i = 0; i < tamanho; i++){
		//preenche todos os campos do vetor com -1, que e o valor indicativo para
		//parar de concatenar o vetor em uma string
		ascii[i] = VECTOR_TERMINATOR;
	}

	str_to_ascii(mensagem, ascii, tamanho);
	concatenar_vetor(ascii, mensagem_saida, tamanho, VECTOR_TERMINATOR);
	split_ascii(mensagem_saida, ascii, strlen(mensagem_saida), totiente);
	concatenar_vetor(ascii, mensagem_saida, strlen(mensagem_saida), VECTOR_TERMINATOR);
	for(i = 0; i < tamanho; i++){
		if(ascii[i] == -1) break;
		ascii[i] = cifrar(ascii[i], menor_coprimo(totiente), modulo);
	}
	concatenar_vetor(ascii, mensagem_saida, tamanho, VECTOR_TERMINATOR);
}

int main(int argc, char *argv[]) {
	// leitura dos parametros de entrada
	char imagem_entrada[MAX_STRING_SIZE];
	char mensagem[MAX_STRING_SIZE];
	char imagem_saida[MAX_STRING_SIZE];
	int p = atoi(argv[4]);
	int q = atoi(argv[5]);
	int n = p * q;
	int tamanho_mensagem;
	int totiente = totiente_primos(p, q);
	//a mensagem de saida tera no maximo MAX_STRING_SIZE vezes o numero de digitos de p * q
	char mensagem_saida[MAX_STRING_SIZE * log10_teto(n)];
	
	if(!e_primo(p) || !e_primo(q)){
		// termina o programa caso p ou q nao sejam primos
		printf("ERRO: p e q devem ser numeros primos.\n");
		return INVALID_PARAMETERS;
	}
	if(n < 9){
		//garante que n e pelo menos 9, caso contrario qualquer digito da tabela ASCII
		//que seja maior que n quebrara o codigo na etapa de segmentacao da mensagem
		printf("ERRO: o produto de p por q deve ser maior ou igual a 9.\n");
		return INVALID_PARAMETERS;
	}

	//assimila as strings passadas
	strcpy(imagem_entrada, argv[1]);
	strcpy(mensagem, argv[2]);
	strcpy(imagem_saida, argv[3]);

	tamanho_mensagem = strlen(mensagem);

	codificar(mensagem, mensagem_saida, tamanho_mensagem, n, totiente);
	printf("Enciptada: %s\n", mensagem_saida);
	return 0;
}
