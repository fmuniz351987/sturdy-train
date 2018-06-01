#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"

#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

int main(int argc, char **argv) {
	// char *imagem_codificada = argv[1];
	char delimitador = argv[2][0];
	char *chave = argv[3];
	FILE *chave_privada;
	int n, d;

	if(argc != 4){
		printf("Por favor, use o formato correto: \n");
		printf("$./decodificador.out imagem_encriptada . chave_privada.txt");
		return INVALID_PARAMETERS;
	}
	chave_privada = fopen(chave, "r");
	fscanf(chave_privada, "%d\n%d", &n, &d);
	printf("Chave privada: (%d,%d)\n", n, d);
	printf("Delimitador: %c\n", delimitador);
	fclose(chave_privada);
	return 0;
}
