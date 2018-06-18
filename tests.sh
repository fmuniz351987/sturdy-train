./codificador.out a AEDS codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDS codificada.txt 101 37
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDSA codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDSAE codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDSAED codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDSAEDSAEDS codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a AEDSAEDSAEDSOIDASCOE codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a asodnc39fin3ew9ni19wrne9wocjun1wasdcijadbsc9r327ygf76cbhds codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

./codificador.out a asdi1j30d9iqwjdpoqwcw/sff240 codificada.txt 37 31
./decodificador.out codificada.txt . private.txt

./codificador.out a aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa codificada.txt 31 29
./decodificador.out codificada.txt . private.txt

./codificador.out a "Ola, por favor me traga 75 cafes!" codificada.txt 37 31
./decodificador.out codificada.txt . private.txt

./codificador.out a "Ola, por favor me traga 75 cafes!" codificada.txt 29 31
./decodificador.out codificada.txt . private.txt

echo "----Erros esperados----"
./codificador.out a AEDS codificada.txt 3 2
./codificador.out a AEDS codificada.txt -3 3
./codificador.out a AEDS codificada.txt -11 31
./codificador.out a AEDS codificada.txt 0 12
./codificador.out a AEDS codificada.txt 2 2
./codificador.out a AEDS codificada.txt 11 13
./codificador.out a AEDS codificada.txt 2 11
./codificador.out a AEDS codificada.txt 2 31
