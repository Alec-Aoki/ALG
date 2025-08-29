# Dado um valor total e uma lista de moedas,
# verifica se há uma combinação válida de moedas
# para alcançar o troco
# O(2^n)
n = int(input())
lista = [int(x) for x in input().rstrip().split(' ')]

def troco(soma, lista_atual):
    if soma == 0:
        return True
    
    if len(lista_atual) == 0 or soma < 0:
        return False
    
    res1 = troco(soma - lista_atual[0], lista_atual[1:])
    res2 = troco(soma, lista_atual[1:])

    return res1 or res2

print(troco(n, lista))