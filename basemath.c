/* esse modulo contem funcoes basicas de matematica que sao usadas ao longo
dos modulos principais.*/ 

int totiente_primos(int p, int q) {
	// calcula o totiente de dois numeros primos p e q.
	return (p - 1) * (q - 1);
}

int e_primo(int x) {
	if(x < 2) return 0;
	//retorna 0 se x nao e primo ou 1 caso contrario.
	for(int i = 2; i < x; i++) {
		if(x % i == 0) return 0;
		if(x < i * i) break;	//para de testar quando i > sqrt(x) sem precisar calcular sqrt(x)
	}
	return 1;
}

int min(int x, int y) {
	//retorna o valor minimo de x e y
	if(x < y) return x;
	return y;
}

int mdc(int x, int y){
	//retorna o maximo divisor comum (MDC) de x e y
	int divisor = 1;
	for(int i = 2; i <= min(x,y); i++) {
		if((x % i == 0) && (y % i == 0)){
			divisor = i;
		}
	}
	return divisor;
}

int log10_teto(int x) {
	// retorna quantos digitos um numero (base decimal) tem
	int i = 0;
	while(x >= 10){
		x /= 10;
		i ++;
	}
	return i + 1;
}

int menor_coprimo(int x){
	//retorna o menor coprimo de x, ou seja, o menor numero de mdc = 1 com x
	for(int i = 2; i < x; i++){
		if(mdc(x, i) == 1){
			return i;
		}
	}
	return 1;
}