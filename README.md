# Trabalho prático: RSA
Aluno: Felipe Ribas Muniz

## Introdução
Este programa está dividido em 4 módulos essenciais, e 2 programas principais, um programa de teste unitário e um script de testes globais: 
- codificador.c - programa principal de codificação
- decodificador.c - programa principal de decodificação
- unittest.c é um programa à parte feito exclusivamente para fins de debugging e testes unitários das funções usadas nos módulos essenciais
- tests.sh é um script de testes globais
- basemath - funções básicas de matemática
- strascii - funções de tratamento de strings e números, concatenação, conversão ascii / caracteres, etc.
- ioarquivos - para leitura e gravação dos arquivos usados pelo programa
- rsa - funções de codificação e decodificação

Além disso, o arquivo makefile contém informações sobre como a compilação deve ser feita e é um script básico que pode ser executado pelo comando:

```bash
$make
```
O arquivo codificador.c contém o programa principal responsável por executar a primeira parte do código, que envolve a codificação da mensagem passada como argumento. Uma vez compilado, ele deve ser executado da seguinte forma:

```bash
$./codificador.out imagem_entrada.ppm "mensagem a esconder" imagem_saida.ppm p q
```

Onde p e q devem ser números primos.

Para decodificar, use:
```bash
$./decodificador.out imagem_codificada.ppm 'delimitador' chave_privada.txt
```
## Funcionamento do codificador
O codificador, inicialmente, pega os valores fornecidos de p e q, encontra n tal que `n = p * q`, e calcula o totiente de n, caso p e q sejam primos, tal que `totiente(n) = (p - 1) * (q - 1)`. Em seguida, a mensagem a ser codificada é convertira em valores ASCII, concatenada em um único bloco, e enfim re-dividida em blocos menores do que o totiente de n. Quando um bloco começa com zero, esse bloco será nulo, de tal forma que o zero seja preservado para ser decodificado posteriormente. Por fim, esses blocos são 'estufados' (_padding_) com zeros à sua esquerda até terem o mesmo número de dígitos de n. Eles são, então, concatenados, e a mensagem codificada é o resultado dessa concatenação.

A mensagem codificada é gravada no arquivo de nome fornecido no campo 'imagem_saida.ppm'. Atualmente, o prorgama só trabalha com arquivos de texto. A chave privada é armazenada em um arquivo chamado 'private.txt'.

## Funcionamento do decodificador
Inicialmente, o decodificador lê o arquivo 'chave_privada.txt' fornecido como terceiro parâmetro no terminal. Depois, a mensagem encriptada é lida no arquivo definido no parâmetro 'imagem_codificada.ppm'. A leitura irá até o momento que for encontrado um caractere dado por 'delimitador'; para fins desse programa, esse caractere é um ponto (.). A mensagem lida, então, é dividida em blocos de tamanho igual ao número de dígitos de n (lido na chave privada), convertida em um vetor de inteiros, que é então decriptado usando n e o expoente de decifragem lidos em `private.txt`. Esse vetor é concatenado, e então separado em números menores que 256, para encontrar seus caracteres ASCII (não funciona para caracteres não-imprimíveis, ou seja, aqueles menores que 32). Por fim, os valores inteiros de ASCII são transformados em caracteres, e a mensagem desencriptada é impressa na tela.
