# Trabalho prático - AEDS 1: RSA
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
make
```
O arquivo codificador.c contém o programa principal responsável por executar a primeira parte do código, que envolve a codificação da mensagem passada como argumento. Uma vez compilado, ele deve ser executado da seguinte forma:

```bash
./codificador.out imagem_entrada.ppm "mensagem a esconder" imagem_saida.ppm p q
```

Onde p e q devem ser números primos.

Para decodificar, use:
```bash
./decodificador.out imagem_codificada.ppm 'delimitador' chave_privada.txt
```
## Funcionamento do codificador
O codificador, inicialmente, pega os valores fornecidos de p e q, encontra n tal que `n = p * q`, e calcula o totiente de n, caso p e q sejam primos, tal que `totiente(n) = (p - 1) * (q - 1)`. Em seguida, a mensagem a ser codificada é convertira em valores ASCII, concatenada em um único bloco, e enfim re-dividida em blocos menores do que o totiente de n. Quando um bloco começa com zero, esse bloco será nulo, de tal forma que o zero seja preservado para ser decodificado posteriormente. Por fim, esses blocos são 'estufados' (_padding_) com zeros à sua esquerda até terem o mesmo número de dígitos de n. Eles são, então, concatenados, e a mensagem codificada é o resultado dessa concatenação.

A mensagem codificada é gravada no arquivo de nome fornecido no campo 'imagem_saida.ppm'. Atualmente, o prorgama só trabalha com arquivos de texto. A chave privada é armazenada em um arquivo chamado 'private.txt'.

## Funcionamento do decodificador
Inicialmente, o decodificador lê o arquivo 'chave_privada.txt' fornecido como terceiro parâmetro no terminal. Depois, a mensagem encriptada é lida no arquivo definido no parâmetro 'imagem_codificada.ppm'. A leitura irá até o momento que for encontrado um caractere dado por 'delimitador'; para fins desse programa, esse caractere é um ponto (.). A mensagem lida, então, é dividida em blocos de tamanho igual ao número de dígitos de n (lido na chave privada), convertida em um vetor de inteiros, que é então decriptado usando n e o expoente de decifragem lidos em `private.txt`. Esse vetor é concatenado, e então separado em números menores que 256, para encontrar seus caracteres ASCII (não funciona para caracteres não-imprimíveis, ou seja, aqueles menores que 32). Por fim, os valores inteiros de ASCII são transformados em caracteres, e a mensagem desencriptada é impressa na tela.

## basemath
Esse módulo possui algumas funções matemáticas básicas usadas ao longo do programa para cálculos necessários como, por exemplo, o totiente de dois primos, o MDC de dois números, etc.

- `totiente_produto(int p, int q)` retorna `(p-1)*(q-1)` caso p e q sejam primos, ou calcula o totiente de `p*q` caso contrário.
- `ndigitos(int x)` retorna quantos dígitos tem um número; por exemplo, `ndigitos(12345)` retorna `5`.
- `potencia10(int expoente)` retorna `10` elevado a `expoente`.
- `e_primo(int x)` retorna 1 caso x seja primo ou 0 caso contrário.

## ioarquivos
Esse módulo nada mais é que um leitor de arquivos que retorna o arquivo lido como uma string ou conta o número de caracteres desse arquivo.
- `tamanho_arquivo(char *caminho_arquivo, char delimitador)` retorna quantos caracteres tem um arquivo desde o início até encontrar o caractere definido em `delimitador`.
- `ler_arquivo(char *caminho_arquivo, char delimitador)` retorna uma string com todos os caracteres lidos de um arquivo até encontrar o caractere definido em `delimitador`.

## RSA
Esse módulo contém as funções principais de codificação usadas pelo algoritmo de RSA no programa.
- `cifrar(int mensagem, int expoente, int modulo)` é a função fundamental do módulo. Ela retorna o valor de `mensagem` elevado a `expoente` e tirado o módulo `modulo`.
- `codificar` é meramente uma função que itera sobre um vetor de inteiros chamando `cifrar` em cada um deles. 
- `padding(int numero, int digitos)` é a função responsável por estufar um número qualquer com zeros à esquerda até que ele tenha o número de dígitos desejado, e retorna esse número 'estufado' como uma string. Assim, por exemplo, `padding(91, 4)` retorna `"0091"` e `padding(80, 2)` retorna `"80"`. Essa função foi criada para que o decodificador pudesse saber como separar a string codificada, pois cada bloco codificado teria um tamanho fixo. Além disso, esse método apresenta maior segurança do que colocar um delimitador entre cada bloco, uma vez que o delimitador pode tornar a codificação mais óbvia e fácil de ser decifrada.
- `pad_sequence` é meramente uma versão de `padding` que itera sobre um vetor de inteiros e retorna todos eles estufados e concatenados numa única string, de forma semelhante a `codificar` comparada a `cifrar`.

Tanto as funções `cifrar` e `padding` foram separadas em uma função que age individualmente sobre um inteiro e outra que age sobre um vetor de inteiros, por maior facilidade de testagem unitária e de manutenção de código. No projeto final, apenas `codificar` e `pad_sequence` foram usadas diretamente (já que elas englobam as outras duas).

## strascii
Esse módulo contém as partes mais fundamentais do código, associadas a concatenação de strings, slices de strings, conversão de ascii para texto, texto para ascii, separação de strings em blocos, etc. Aqui, foram criadas funções que permitissem maior maleabilidade de strings e vetores, de tal forma a tornar a linguagem C um pouco mais parecida com linguagens mais simples como Python, que permitem certa facilidade com manuseamento de strings e vetores no geral. Alguns dos pontos centrais desse módulo são:

Foi definida uma constante VECTOR_TERMINATOR que, para fins de praticidade, usa o valor `-1` para indicar o fim de um vetor. Em alguns casos, era possível saber o tamanho máximo de um vetor, mas não quantos elementos dele eram váludos, devido à forma arbitrária e imprevisível como a divisão em blocos era feita, dependendo dos valores fornecidos de `p` e `q`. Para efeitos práticos, o VECTOR_TERMINATOR tem exatamente o mesmo efeito do caractere NULL TERMINATOR `('\0')` em strings. Como, nesse projeto, não foram trabalhados números negativos, então essa escolha do número negativo mais simples foi tida como o melhor 'alerta' indicando que o vetor terminava ali (apesar de poder ter mais valores lixo alocados adiante). Em toda iteração adiante, sempre é feito o teste para confirmar se o elemento iterado é diferente de -1. O teste não avalia para qualquer valor negativo, pois isso poderia funcionar, aleatoriamente, com valores lixo de memória, e tornaria a testagem e debuggagem mais complicada e difícil de encontrar a causa do problema. A constante foi definida no topo do módulo, e, apesar de ser mais verboso escrever VECTOR_TERMINATOR no lugar de -1, é mais legível dessa maneira, e também permite que, caso a escolha do -1 tivesse sido ruim, seria mais fácil alterar apenas a constante do que alterar todos os casos onde -1 foi utilizado.

- A função `tamanho_vetor` é semelhante à função `len()` em python. Ela itera sobre os elementos de um vetor e para de contar seus elementos quando encontra `-1`, ou seja, o VECTOR_TERMINATOR, e retorna a contagem de elementos do vetor.
- A função `caractere_imprimivel` testa se um valor ASCII é um caractere legível, e não um comando ASCII (ou seja, se o valor está entre 32 (espaço) e 255 (non-breaking space). Ela foi deprecada ao longo do projeto por acabar sendo redundante a outras, mas ficou no módulo pois foi muito usada durante debugging quando o código decodificava de forma errada caracteres inválidos. Ela foi usada antes da implementação do padding, e mesmo assim não funcionava como esperado. Era preciso que houvesse distinção clara entre os blocos codificados para poder obter de fato os valores ASCII corretos, e, depois que o padding foi implementado, simplesmente usar a divisão em blocos menores ou iguais a 255 foi suficiente para obter os caracteres originais, assumindo que a mensagem original seria composta apenas de caracteres imprimíveis. Isso porque, se pegarmos o maior valor possível até 255, é impossível que haja um caractere válido que possa ser interpretado como, por exemplo, 12 5 ou 125, pois 12 e 5 não são válidos. Além disso, o bloco 34128 não poderia ser dividido como 341 28, pois 341 é maior que 255.
- `str_to_ascii` transforma uma string em um vetor de inteiros, onde cada elemento inteiro é um valor ASCII da string original.
- `ascii_to_str` faz o exato oposto e transforma um vetor de ASCII em uma string.
- `strslice` corta uma string de forma semelhante ao slice do python. Assim, `strslice("01234567", 2, 6)` retorna `"2345"`, uma vez que o valor de término da string é excluído. Ela equivale ao código python de slice `"01234567"[2:6]`.
- `concatenar_vetor` pega um vetor de inteiros e transforma em uma string contínua com todos os valores fornecidos.
- `quebrar_em_blocos` divide uma string de números em blocos cujo tamanho máximo é o tamanho fornecido (ou seja, no algoritmo, é o totiente de `p * q`), ou `255` na decodificação.
- `quebrar_em_blocos_de_tamanho_fixo` é usada pelo decodificador para separar uma string em blocos que possuem o mesmo número de dígitos que `p * q`. Ela absolutamente exige que uma técnica de *padding* tenha sido implementada para funcionar devidamente.
- `converter_para_ascii_e_dividir` é usada pelo codificador para transformar uma mensagem em um vetor de ASCII, concatená-la e depois dividi-la em blocos de tamanho menor que o totiente de n.
