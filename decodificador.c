#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"
#include "ioarquivos.h"

#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

int main(int argc, char **argv) {
	char *imagem_codificada = argv[1];
	char delimitador = argv[2][0];
	char *chave = argv[3];
	FILE *file;
	int n, d;
	char *mensagem_codificada;
	char *mensagem_original;
	int *codificacao;
	int tamanho_maximo;

	if(argc != 4){
		printf("Por favor, use o formato correto: \n");
		printf("$./decodificador.out \"imagem_encriptada.ppm\" 'terminador' \"chave_privada.txt\"\n\n");
		printf("Exemplo: \n$./decodificador.out codificada.txt . private.txt\n\n");
		return INVALID_PARAMETERS;
	}

	//obtendo a chave privada
	file = fopen(chave, "r");
	fscanf(file, "%d\n%d", &n, &d);
	fclose(file);
	printf("Chave privada: (%d, %d)\n", n, d);
	printf("Delimitador: %c\n", delimitador);
	mensagem_codificada = ler_arquivo(imagem_codificada, delimitador);
	printf("Mensagem codificada: %s\n", mensagem_codificada);
	codificacao = converter_para_ascii_e_dividir(mensagem_codificada, n, 0);
	mensagem_original = codificar(codificacao, n, d);
	tamanho_maximo = strlen(mensagem_original);
	free(codificacao);
	codificacao = converter_para_ascii_e_dividir(mensagem_original, 256, 0);
	free(mensagem_original);
	mensagem_original = ascii_to_str(codificacao, tamanho_maximo);
	printf("Decodificada: %s\n", mensagem_original);
	free(mensagem_codificada);
	free(codificacao);
	printf("\n\n");
	return 0;
}
