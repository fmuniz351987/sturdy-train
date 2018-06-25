/* esse modulo contem funcoes basicas de matematica que sao usadas ao longo
dos modulos principais.*/ 

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

int e_primo(int x) {
	//retorna 0 se x nao e primo ou 1 caso contrario.
	if(x < 2) return 0;
	for(int i = 2; i < x; i++) {
		if(x % i == 0) return 0;
		if(x < i * i) break;	//para de testar quando i > sqrt(x) sem precisar calcular sqrt(x) (que é menos eficiente)
	}
	return 1;
}

int totiente_produto(int p, int q) {
	// calcula o totiente de dois numeros p e q.
	int n_coprimos = 0;
	int produto = p * q;

	if(e_primo(p) && e_primo(q)) return (p - 1) * (q - 1);	//caso p e q sejam primos, não é necessário fazer muitos cálculos
	for(int i = 1; i < produto; i++) {
		if(mdc(i, produto) == 1) n_coprimos++;
	}
	return n_coprimos;
}

int ndigitos(int x) {
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

int inverso_modular(int a, int b)
{
	// retorna o inverso modular de a em b.
	int b0 = b, t, q;
	int x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

int potencia10(int expoente){
	// retorna 10 elevado ao expoente fornecido
	int num = 1;
	for(int i = 0; i < expoente; i++) num *= 10;
	return num;
}
