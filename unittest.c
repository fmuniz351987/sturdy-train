// modulo de testes e debugging
#include <stdio.h>
#include <stdlib.h> // funcao atoi()
#include <string.h>
#include <math.h>

#include "basemath.h"
#include "strascii.h"
#include "rsa.h"

#define MAX_STRING_SIZE 100

	char *supertexto = "\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla massa libero, \
ullamcorper eu dictum at, tincidunt eget nisi. Vestibulum pharetra lectus enim, \
sit amet pharetra augue porta vel. Duis ut finibus elit. Maecenas accumsan eros \
at turpis fringilla laoreet. Integer rutrum, ex et sodales sollicitudin, magna \
nibh laoreet orci, sit amet cursus arcu arcu eget odio. Nunc congue odio ut ante \
auctor efficitur.";

	char *supertexto_codificado = "\
866926822124499803983586944994545251639922747911393612134218918882705151611059\
854680365831889643612479115899814781563199397340196491016790370447314568177974\
484382556159141001910182398660171907314568184936812687969268850958228509100198\
891318821797683723447326319781560453188997885096274871558668738833168782123473\
298558695411611380674191228715175427109649854267510372850989884791463192274791\
139361213423717806741912287151754271088869631888775646326828997797102138317903\
215382157567119037179874479187382531103728509831747913683474612854898888862872\
354191279522996274340139864545287768371901703986158998148509920247915520479197\
572710568171143986516118916885375647326274871538633671768339865869463134014734\
340137179227454561210182756792274545975710019101994732586947918660850944843756\
271051619853863760454581998715586645452416981922747911393612134237177938362421\
318821688862416716988862416716922128841371773839826961390370448264987236818988\
937458698775898847919475318813938886473288865283681445939340145742178151016731\
881655";

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

	assert(123 == strslice(text, 0, 3));
	assert(0 == strslice(text, 0, 0));
	assert(1 == strslice(text, 0, 1));
	assert(9751 == strslice(text, 4, 8));
	assert(4 == strslice(text, 11, 12));
	assert(4958130 == strslice(longtext, 31, 39));
	assert(5034 == strslice(longtext, tamanho - 4, tamanho));
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
	// imprimir_vetor(ascii, 9);
	for(int i = 0; i < tamanho && vetor_esperado[i] != -1; i++){
		// printf("Esperado: %d\nCalculado: %d\n", vetor_esperado[i], ascii[i]);
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

void testar_cifragem_e_decifragem(){
	printf("Testando decifragem e cifragem individualmente...\n");
	int cifrado, decifrado;
	int exp_cifragem = 11;
	int modulo = 899;
	int exp_decifragem = 611;
	for(int i = 0; i < modulo; i++){
		cifrado = cifrar(i, exp_cifragem, modulo);
		decifrado = cifrar(cifrado, exp_decifragem, modulo);
		assert(decifrado == i);
		// printf("i: %d, %d, %d\n", i, cifrado, decifrado);
	}
}

// void testar_codificar(char *mensagem, char *saida_esperada, int p, int q){
// 	printf("Testando codificacao...\n");
// 	int totiente = (p-1)*(q-1);
// 	int modulo = p * q;
// 	char *mensagem_saida;
// 	mensagem_saida = codificar(mensagem, modulo, totiente);
// 	assert(!strcmp(mensagem_saida, saida_esperada));
// 	printf("Esperada:%s\nCalculada:%s\n", saida_esperada, mensagem_saida);
// 	free(mensagem_saida);
// }

void testar_caracteres_imprimiveis(){
	for(int i = 0; i < 256; i++){
		if(caractere_imprimivel((char) i)){
			printf("%c", (char) i);
		}
	}
	printf("\n");
}

void testar_converter_ascii_e_dividir(){
	int *mensagem_dividida;
	char *mensagem = "Alo mundo!";
	int maximo = 111;
	printf("Testando divisao de mensagem...\n");
	mensagem_dividida = converter_para_ascii_e_dividir(mensagem, maximo);
	for(int i = 0; mensagem_dividida[i] != -1; i++){
		// printf("%d ", mensagem_dividida[i]);
	}
	// printf("\n");
	assert(mensagem_dividida[0] == 65);
	assert(mensagem_dividida[1] == 108);
	assert(mensagem_dividida[2] == 111);
	assert(mensagem_dividida[3] == 32);
	assert(mensagem_dividida[4] == 109);
	assert(mensagem_dividida[5] == 11);
	assert(mensagem_dividida[6] == 71);
	assert(mensagem_dividida[7] == 101);
	assert(mensagem_dividida[8] == 0);
	assert(mensagem_dividida[9] == 0);
	assert(mensagem_dividida[10] == 111);
	assert(mensagem_dividida[11] == 33);
	assert(mensagem_dividida[12] == -1);

	free(mensagem_dividida);
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
	testar_str_to_ascii();
	testar_ascii_to_str(n_testes);
	testar_strslice();
	testar_concatenar_vetor();
	testar_split_ascii();
	testar_cifrar();
	// testar_codificar("AEDS", "83160237844", 29, 31);
	// testar_codificar("AEDSAEDS", "83160237847631937844", 29, 31);
	// testar_codificar("Mensagem secreta!", 
	//                  "12551110154397513022700156312612167250396117602187",
	//                  101, 31);
	// testar_codificar("Mensagem secreta!", 
	//                  "12551110154397513022700156312612167250396117602187",
	//                  101, 31);
	// testar_codificar(supertexto, supertexto_codificado, 101, 103);
	testar_caracteres_imprimiveis();
	testar_cifragem_e_decifragem();
	testar_converter_ascii_e_dividir();
	return 0;
}
