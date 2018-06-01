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
	// char *imagem_codificada = argv[1];	#a ser usado na parte 2
	char delimitador = argv[2][0];
	char *chave = argv[3];
	FILE *chave_privada;

	chave_privada = fopen(chave, "r");
	return 0;
}
