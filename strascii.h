int* str_to_ascii(char *mensagem);

char* ascii_to_str(int *ascii, int tamanho);

int strslice(char *texto, int inicio, int fim);

char *concatenar_vetor(int *vetor, int tamanho, int invalido);

int *quebrar_em_blocos(char *mensagem, int totiente, int vector_terminator);

void imprimir_vetor(int *vetor, int tamanho);

int caractere_imprimivel(char caractere);

int tamanho_vetor_terminado(int *vetor, int vector_terminator);

int *quebrar_em_blocos_de_tamanho_fixo(char *mensagem, int tamanho_bloco);