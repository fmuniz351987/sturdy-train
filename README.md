# Trabalho prático: RSA
Aluno: Felipe Muniz
## Introdução

Este programa está dividido em 2 módulos e 2 arquivos principais: 
- codificador.c
- decodificador.c
- basemath.c / basemath.h
- strascii.c / strascii.h

Além disso, o arquivo compile.sh contém informações sobre como a compilação deve ser feita e é um script básico que pode ser executado pelo comando:

```bash
bash compile.sh
```
O arquivo codificador.c contém o programa principal responsável por executar a primeira parte do código, que envolve a codificação da mensagem passada como argumento. Uma vez compilado, ele deve ser executado da seguinte forma:

```bash
codificador.c imagem_entrada.ppm "mensagem a esconder" imagem_saida.ppm p q
```
Onde p e q devem ser números primos.