#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>

#include "rsa.h"
#include "basemath.h"

#define MAX_STRING_SIZE 100
#define INVALID_PARAMETERS 1

int main(int argc, char *argv[]) {
	// leitura dos parametros de entrada
	// char *imagem_entrada = argv[1];
	char *mensagem = argv[2];
	// char *imagem_saida = argv[3];
	int p = atoi(argv[4]);
	int q = atoi(argv[5]);
	int n = p * q;
	int totiente = totiente_primos(p, q);
	//a mensagem de saida tera no maximo MAX_STRING_SIZE vezes o numero de digitos de p * q
	char *mensagem_saida = (char*) malloc((strlen(mensagem) * ndigitos(n) + 1)*sizeof(char));
	
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
	for(int i = 1; i < 4; i++){
		if(strlen(argv[i]) >= MAX_STRING_SIZE){
			printf("ERRO: cada parametro deve ter no maximo %d caracteres.\n", MAX_STRING_SIZE);
			return INVALID_PARAMETERS;
		}
	}

	mensagem_saida = codificar(mensagem, n, totiente);
	printf("Encriptada: %s\n", mensagem_saida);
	free(mensagem_saida);
	return 0;
}
