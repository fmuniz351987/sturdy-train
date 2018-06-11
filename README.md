# Trabalho prático: RSA
Aluno: Felipe Ribas Muniz
## Introdução

Este programa está dividido em 4 módulos essenciais, e 2 programas principais, um programa de teste unitário, um script de testes globais e um código python: 
- codificador.c - programa principal de codificação
- decodificador.c - programa principal de decodificação
- unittest.c é um programa à parte feito exclusivamente para fins de debugging e testes unitários das funções usadas nos módulos essenciais
- tests.sh é um script de testes globais
- basemath - funções básicas de matemática
- strascii - funções de tratamento de strings e números, concatenação, conversão ascii / caracteres, etc.
- ioarquivos - para leitura e gravação dos arquivos usados pelo programa
- rsa - funções de codificação e decodificação
- cifrar2931.py é um arquivo de teste usando uma linguagem de programação mais simples para comparar com resultados esperados sem precisar preocupar com ponteiros.

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

O programa de decodificação ainda está em fase de testes.
