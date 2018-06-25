int cifrar(int mensagem, int expoente, int modulo);

void *codificar(int *ascii, int modulo, int expoente_cifragem);

char *padding(int numero, int digitos);

char *pad_sequence(int *vetor, int digitos);
