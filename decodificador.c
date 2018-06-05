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

	if(argc != 4){
		printf("Por favor, use o formato correto: \n");
		printf("$./decodificador.out \"imagem_encriptada.ppm\" 'terminador' \"chave_privada.txt\"\n");
		printf("Exemplo: \n$./decodificador.out codificada.txt . private.txt\n");
		return INVALID_PARAMETERS;
	}

	//obtendo a chave privada
	file = fopen(chave, "r");
	fscanf(file, "%d\n%d", &n, &d);
	printf("Chave privada: (%d,%d)\n", n, d);
	printf("Delimitador: %c\n", delimitador);
	fclose(file);
	mensagem_codificada = ler_arquivo(imagem_codificada, delimitador);
	printf("Mensagem codificada: %s\n", mensagem_codificada);
	mensagem_original = decodificar(mensagem_codificada, n, d);
	printf("Decodificada: %s\n", mensagem_original);
	free(mensagem_codificada);
	return 0;
}
