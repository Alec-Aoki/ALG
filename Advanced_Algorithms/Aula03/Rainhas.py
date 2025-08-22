# Pos. inicial da rainha
i = int(input())
j = int(input())

def check_diagonais(rainhas, r, i):
    for r_a, i_a in enumerate(rainhas):
        if i_a == -1:
            continue
        if abs(r_a - r) == abs(i_a - i):
            return True
    return False

def place_queens(rainhas):
    if not -1 in rainhas:
        return rainhas # Completa
    # Checando todas as linhas
    for r in range(8):
        if rainhas[r] != -1: # Já preenchida
            continue
        # Checando todas as colunas
        for i in range(8):
            if i in rainhas:
                continue
            if check_diagonais(rainhas, r, i):
                continue
            nova_rainhas = rainhas.copy()
            nova_rainhas[r] = i
            res = place_queens(nova_rainhas)
            if len(res) != 0:
                return res
    return []

rainhas_init = [-1] * 8
rainhas_init[i] = j
print(place_queens(rainhas_init))