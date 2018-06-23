#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>

#include "rsa.h"
#include "basemath.h"
#include "strascii.h"

#define INVALID_PARAMETERS 1
#define VECTOR_TERMINATOR -1

void validar_primos(int p, int q)
{
	// confere se os valores fornecidos de p e q são válidos.
	if(!e_primo(p) || !e_primo(q)){
		// termina o programa caso p ou q nao sejam primos
		printf("ERRO: p e q devem ser numeros primos.\n");
		exit(INVALID_PARAMETERS);
	}
	if(p * q < 255){
		//garante que n e pelo menos 9, caso contrario qualquer digito da tabela ASCII
		//que seja maior que n quebrara o codigo na etapa de segmentacao da mensagem
		printf("ERRO: o produto de p por q deve ser maior ou igual a 255.\n");
		exit(INVALID_PARAMETERS);
	}

}


int main(int argc, char *argv[]) {
	// char *imagem_entrada = argv[1];	//sera usada na segunda parte do TP
	char *mensagem = argv[2];
	char *imagem_saida = argv[3];		//atualmente codificada.txt nos testes; será um ppm na parte 2
	FILE *arquivo_saida;
	int p = atoi(argv[4]);
	int q = atoi(argv[5]);
	int n = p * q;
	int totiente = totiente_primos(p, q);
	int e = menor_coprimo(totiente);	//expoente de cifragem
	int d = inverso_modular(e, totiente);	//expoente de decifragem
	char *mensagem_saida;
	char *chave = (char*) malloc(sizeof(char) * 100);
	int *codificacao;
	FILE *file_pkey;	//arquivo de saida da chave privada
	
	validar_primos(p, q);
	
	//codificando
	codificacao = converter_para_ascii_e_dividir(mensagem, totiente, 1);
	codificar(codificacao, n, e);
	mensagem_saida = pad_sequence(codificacao, ndigitos(n));
	free(codificacao);
	printf("Encriptada: %s\n", mensagem_saida);

	//salvando mensagem externamente
	arquivo_saida = fopen(imagem_saida, "w");	//mudar forma de abertura na imagem (parte 2)
	fprintf(arquivo_saida, "%s.\n", mensagem_saida);
	free(mensagem_saida);
	fclose(arquivo_saida);

	//salvando chave privada externamente em private.txt
	sprintf(chave, "%d\n%d\n", n, d);
	file_pkey = fopen("private.txt", "w");
	fputs(chave, file_pkey);
	free(chave);
	fclose(file_pkey);

	return 0;
}
