exemplo = [1, -1, 1, -1, 1]

# O(n)
def acende(lampadas):
    custo = 0
    for i in range(len(lampadas)):
        l = lampadas[i]
        if (custo % 2 != 0):
            l = -l
        if (l == -1):
            custo += 1
    return custo

print(acende(exemplo))