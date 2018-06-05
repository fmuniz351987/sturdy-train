gcc codificador.c basemath.c strascii.c rsa.c -o codificador.out -lm -Wall -std=c11
gcc decodificador.c basemath.c strascii.c rsa.c ioarquivos.c -o decodificador.out -lm -Wall -std=c11
gcc unittest.c basemath.c strascii.c rsa.c -o unittest.out -lm -Wall -std=c11
