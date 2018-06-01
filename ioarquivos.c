#include <stdio.h>
#include <stdlib.h>

int tamanho_arquivo(char *caminho_arquivo, char delimitador)
//retorna o numero de caracteres de um arquivo
{
	char caractere_atual = 'a';
	int file_size = 0;
	FILE *file;

	file = fopen(caminho_arquivo, "r");
	//numero de caracteres da mensagem
	while(caractere_atual != delimitador){
		fscanf(file, "%c", &caractere_atual);
		file_size++;
	}
	fclose(file);

	return file_size;
}

char *ler_arquivo(char *caminho_arquivo, char delimitador)
{
	// retorna um ponteiro para a string correspondente a leitura de um arquivo fornecido.
	int tamanho;
	FILE *file;
	char *mensagem_codificada;

	tamanho = tamanho_arquivo(caminho_arquivo, delimitador);
	// printf("Numero de caracteres: %d\n", tamanho);
	mensagem_codificada = (char*) malloc(sizeof(char) * tamanho);

	//copiando o conteudo do arquivo para uma string
	file = fopen(caminho_arquivo, "r");
	for(int i = 0; i < tamanho; i++){
		fscanf(file, "%c", &mensagem_codificada[i]);
	}
	fclose(file);
	mensagem_codificada[tamanho - 1] = '\0';

	return mensagem_codificada;
}
