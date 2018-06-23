#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"
#include "ioarquivos.h"

#define INVALID_PARAMETERS 1

void testar_parametros(int argc)
{
	if(argc != 4){
		printf("Por favor, use o formato correto: \n");
		printf("$./decodificador.out \"imagem_encriptada.ppm\" 'terminador' \"chave_privada.txt\"\n\n");
		printf("Exemplo: \n$./decodificador.out codificada.txt . private.txt\n\n");
		exit(INVALID_PARAMETERS);
	}
}

int main(int argc, char **argv) {
	char *imagem_codificada = argv[1];
	char delimitador = argv[2][0];
	char *chave = argv[3];
	FILE *file;
	int n, d;
	char *mensagem_codificada;
	char *mensagem_original;
	int *codificacao;

	testar_parametros(argc);

	// obtendo a chave privada
	file = fopen(chave, "r");
	fscanf(file, "%d\n%d", &n, &d);
	fclose(file);
	printf("Chave privada: (%d, %d)\n", n, d);

	// lendo mensagem codificada
	mensagem_codificada = ler_arquivo(imagem_codificada, delimitador);

	// quebrando mensagem em blocos cifrados
	codificacao = quebrar_em_blocos_de_tamanho_fixo(mensagem_codificada, ndigitos(n));
	free(mensagem_codificada);

	// decodificando os blocos
	codificar(codificacao, n, d);

	// re-fazendo a divisão dos blocos para ASCII
	mensagem_original = concatenar_vetor(codificacao);
	free(codificacao);
	codificacao = quebrar_em_blocos(mensagem_original, 256);
	free(mensagem_original);

	// transformando o vetor ascii em uma string
	mensagem_original = ascii_to_str(codificacao);
	free(codificacao);
	printf("Mensagem original: \n");
	printf("%s\n", mensagem_original);
	free(mensagem_original);

	return 0;
}
