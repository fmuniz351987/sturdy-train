#este arquivo é apenas um modelo para o programa final, e foi usado para testes 
#e comparações com os resultados em C. nenhuma parte desse código foi efetivamente
#implementada no programa final.

def mdc(x, y):
    mdiv = 1
    for i in range(2, max([x,y])):
        if x % i == 0 and y % i == 0:
            mdiv = i
    return mdiv

def menor_coprimo(x):
    for i in range(2,x):
        if mdc(i,x) == 1:
            return i
    return 1

def cifrar(mensagem:str, p:int=29, q:int=31):
    modulo = p*q
    totiente = (p-1)*(q-1)
    expoente = menor_coprimo(totiente)
    vetorascii = [str(ord(valor)) for valor in mensagem]
    # print(vetorascii)
    mensagem = "".join(vetorascii)
    print(vetorascii)
    codificado = []
    tamanho = len(mensagem)
    i = 0
    while i < tamanho:
        for j in range(i+1, tamanho + 1):
            submensagem = mensagem[i:j]
            if int(submensagem) >= totiente:
                codificado.append(int(submensagem[0:-1]))
                i = j - 1
                break
            if int(mensagem[i:tamanho]) < totiente:
                codificado.append(int(mensagem[i:tamanho]))
                i = tamanho
                break
    print(codificado)
    for i, value in enumerate(codificado):
        codificado[i] = str(value ** expoente % modulo)
    return "".join(codificado)
