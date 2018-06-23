#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"
#include "ioarquivos.h"

#define INVALID_PARAMETERS 1

int main(int argc, char **argv) {
	char *imagem_codificada = argv[1];
	char delimitador = argv[2][0];
	char *chave = argv[3];
	FILE *file;
	int n, d;
	char *mensagem_codificada;
	char *mensagem_original;
	int *codificacao;

	if(argc != 4){
		printf("Por favor, use o formato correto: \n");
		printf("$./decodificador.out \"imagem_encriptada.ppm\" 'terminador' \"chave_privada.txt\"\n\n");
		printf("Exemplo: \n$./decodificador.out codificada.txt . private.txt\n\n");
		return INVALID_PARAMETERS;
	}

	// obtendo a chave privada
	file = fopen(chave, "r");
	fscanf(file, "%d\n%d", &n, &d);
	fclose(file);
	printf("Chave privada: (%d, %d)\n", n, d);
	printf("Delimitador: %c\n", delimitador);

	// lendo mensagem codificada
	mensagem_codificada = ler_arquivo(imagem_codificada, delimitador);
	printf("Mensagem codificada: %s\n", mensagem_codificada);

	// quebrando mensagem em blocos cifrados
	codificacao = quebrar_em_blocos_de_tamanho_fixo(mensagem_codificada, ndigitos(n));
	printf("Blocos quebrados:\n");
	imprimir_vetor(codificacao);

	// decodificando os blocos
	codificar(codificacao, n, d);

	// re-fazendo a divisão dos blocos para ASCII
	mensagem_original = concatenar_vetor(codificacao);
	codificacao = quebrar_em_blocos(mensagem_original, 256);
	printf("Valores ASCII: ");
	imprimir_vetor(codificacao);

	// transformando o vetor ascii em uma string
	mensagem_original = ascii_to_str(codificacao);
	printf("Mensagem original: \n");
	printf("%s\n", mensagem_original);

	//liberando memoria
	// free(mensagem_codificada);
	// free(mensagem_original);
	// free(codificacao);
	return 0;
}
