# Maior subsequência crescente não contínua
lista = [3, 5, 6, 1, 10, 11, 25, 2, 4]

# Força bruta
def forca_bruta(lista, i):
    if i == 0:
        return 1 # Estamos no começo da lista
    
    # Checando todos que dependem desse estado
    lista_ind_dep = [ind for ind, valor in enumerate(lista[:i]) if lista[i] > valor]

    # Pegando a lista de maior tamanho
    max_len = 0
    for ind in lista_ind_dep:
        res = forca_bruta(lista, ind)
        if res > max_len:
            max_len = res

    return 1 + max_len


# Printando o tamanho de todas as sublistas crescentes não contínuas, aí seria só pegar o maior valor
print([forca_bruta(lista, k) for k in range(len(lista))])

# Top down
def pd_td(lista, memo, i):
    if i == 0:
        return 1 # Estamos no começo da lista
    
    # Checando todos que dependem desse estado
    lista_ind_dep = [ind for ind, valor in enumerate(lista[:i]) if lista[i] > valor]

    max_len = 0
    for ind in lista_ind_dep:
        if memo[ind] == 0:
            memo[ind] = pd_td(lista, memo, ind)
        if memo[ind] > max_len:
            max_len = memo[ind]

    return 1 + max_len

memo = [0] * len(lista)
print([pd_td(lista, memo, k) for k in range(len(lista))])

# Bottom up
def pd_bu(lista, memo):
    memo[0] = 1
    
    for i in range(1, len(lista)):
        lista_dep = [memo[ind] for ind, valor in enumerate(lista[:i]) if lista[i] > valor]
        if not lista_dep:
            memo[i] = 1
        else:
            memo[i] = max(lista_dep) + 1

    return max(memo)

memo = [0] * len(lista)
print(pd_bu(lista, memo))