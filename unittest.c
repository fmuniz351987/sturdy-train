// modulo de testes e debugging
#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"

#define MAX_STRING_SIZE 100

int *criar_vetor(int tamanho){
	return (int*) malloc(tamanho * sizeof(int));
}

char *criar_texto(int tamanho) {
	return (char*) malloc(tamanho * sizeof(int) + 1);
}

void assert(int expressao){
	if (!expressao) {
		printf("Erro de asserção.\n");
	}
}

void testar_matematica() {
	printf("Testando matematica...\n");
	assert(totiente_primos(29,31) == 840);
	assert(e_primo(31));
	assert(e_primo(2*3*5*7*11*13*17)+1);
	assert(e_primo(2*3*5*7*11*13*17*23*29)+1);
	assert(!e_primo(8831*8831));
	assert(!e_primo(0));
	assert(!e_primo(1));
	assert(!e_primo(-1));
	assert(!e_primo(-1230941));
	assert(min(-50, 0) == -50);
	assert(min(50, 0) == 0);
	assert(min(-1000, -200) == -1000);
	assert(mdc(100, 25) == 25);
	assert(mdc(23*500, 4000*11) == 500);
	assert(ndigitos(1000) == 4);
	assert(ndigitos(8124) == 4);
	assert(ndigitos(1203985) == 7);
	assert(ndigitos(1) == 1);
	assert(ndigitos(0) == 1);
	assert(ndigitos(10) == 2);
	assert(ndigitos(11) == 2);
	assert(menor_coprimo(2000) == 3);
	assert(menor_coprimo(2*3*5*7*9*11*17) == 13);
}

void preencher_vetor(int *vetor, int tamanho){
	//preenche um vetor com seus propios indices correspondentes
	for(int j = 0; j < tamanho; j++){
		vetor[j] = j+1;
	}
}

void testar_impressao_vetor(int n_testes){
	printf("Testando impressao de vetores...\n");
	for(int i = 1; i <= n_testes; i++) {
		int *vetor = criar_vetor(i);
		preencher_vetor(vetor, i);
		imprimir_vetor(vetor, i);		//funcao sendo testada
		free(vetor);
	}
}

void testar_resetar_vetor(int n_testes){
	printf("Testando reset de vetores...\n");
	for(int i = 0; i < n_testes; i++){
		int *vetor = criar_vetor(i);
		resetar_vetor(vetor, i, 0);
		for(int j = 0; j < i; j++){
			assert(vetor[j] == 0);
		}
		free(vetor);
	}
}

void testar_str_to_ascii(){
	printf("Testando str para ascii...\n");
	char *texto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 ";
	int tamanho = strlen(texto);
	int *vetor = criar_vetor(tamanho);
	vetor = str_to_ascii(texto);
	for(int i = 0; i < tamanho; i++){
		assert(texto[i] == (char) vetor[i]);
	}
	// imprimir_vetor(vetor, tamanho);
	free(vetor);
}

void testar_ascii_to_str(int n_testes){
	printf("Testando ascii para str...\n");
	for(int i = 0; i < n_testes; i++){
		if(i > 255) break;
		int *vetor = criar_vetor(i);
		char *texto = criar_texto(i);
		preencher_vetor(vetor, i);
		ascii_to_str(vetor, i);
		// printf("%s\n", texto);
		free(vetor);
		free(texto);
	}	
}

void testar_strslice(){
	printf("Testando strslice...\n");
	char *text = "123097510934";
	char *longtext = "1230975390458723459137451230953049581301320985034";
	int tamanho = strlen(longtext);

	assert(123 == atoi(strslice(text, 0, 3)));
	assert(0 == atoi(strslice(text, 0, 0)));
	assert(1 == atoi(strslice(text, 0, 1)));
	assert(9751 == atoi(strslice(text, 4, 8)));
	assert(4 == atoi(strslice(text, 11, 12)));
	assert(4958130 == atoi(strslice(longtext, 31, 39)));
	assert(5034 == atoi(strslice(longtext, tamanho - 4, tamanho)));
}

void testar_concatenar_vetor() {
	printf("Testando concatenacao de vetores...\n");
	int vetor1[] = {1,2,3,4,5, -1, 0}, n_v1 = 7,
		vetor2[] = {0,2,0,3,0,6,6,10, 471, -1, 5}, n_v2 = 11;
	char *texto1 = malloc((n_v1 + 1)*sizeof(char));
	char *texto2 = malloc((n_v2 + 1) * sizeof(char));
	texto1 = concatenar_vetor(vetor1, n_v1, -1);
	texto2 = concatenar_vetor(vetor2, n_v2, -1);
	assert(!strcmp(texto1, "12345"));
	assert(!strcmp(texto2, "020306610471"));
	free(texto1); free(texto2);
}

void testar_split_ascii() {
	char *mensagem = "123510394861039485103";
	int tamanho = strlen(mensagem);
	int *ascii;
	int vetor_esperado[] = {123, 510, 394, 86, 103, 94, 85, 103, -1};

	printf("Testando split de ascii...\n");
	ascii = split_ascii(mensagem, 800, -1);
	imprimir_vetor(ascii, 9);
	for(int i = 0; i < tamanho && vetor_esperado[i] != -1; i++){
		printf("Esperado: %d\nCalculado: %d\n", vetor_esperado[i], ascii[i]);
		assert(ascii[i] == vetor_esperado[i]);
	}
	free(ascii);
}

void testar_cifrar(){
	printf("Testando funcao cifrar...\n");
	int mensagem[] = {656, 96, 88, 3};
	int cifrada_esperada[] = {831, 602, 378, 44};
	for(int i = 0; i < 4; i++){
		assert(cifrar(mensagem[i], 11, 899) == cifrada_esperada[i]);
	}
}

void testar_codificar(){
	printf("Testando codificacao...\n");
	char *mensagem = "AEDS";
	int totiente = 840;
	int modulo = 899;
	char *mensagem_saida;
	char *saida_esperada = "83160237844";
	mensagem_saida = codificar(mensagem, modulo, totiente);
	assert(!strcmp(mensagem_saida, saida_esperada));
	free(mensagem_saida);
}

int main(int argc, char **argv) {
	if(argc == 1){
		printf("ERRO: Insira um numero de testes a serem realizados como argumento da \
		       chamada da funcao.\n");
		return 0;
	}
	int n_testes = atoi(argv[1]);
	testar_matematica();
	// testar_impressao_vetor(n_testes);
	testar_resetar_vetor(n_testes);
	testar_str_to_ascii();
	testar_ascii_to_str(n_testes);
	testar_strslice();
	testar_concatenar_vetor();
	testar_split_ascii();
	testar_cifrar();
	testar_codificar();
	return 0;
}
