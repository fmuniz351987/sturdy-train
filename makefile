CC = gcc

CFLAGS = -lm -pedantic -Wall -std=c11

include:

	$(CC) $(CFLAGS) -o codificador.out codificador.c basemath.c strascii.c rsa.c
	$(CC) $(CFLAGS) -o decodificador.out decodificador.c basemath.c strascii.c rsa.c
	$(CC) $(CFLAGS) -o unittest.out unittest.c basemath.c strascii.c rsa.c 
