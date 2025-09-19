vet = [7, 25, 2, 15, 31, 4, 11]

def quickSort(lista):
    if(len(lista) <= 1):
        return lista
    
    pivot  = lista[0] # Polêmico
    lista_a = [x for x in lista[1:] if x < pivot]
    lista_b = [x for x in lista[1:] if x >= pivot]

    return quickSort(lista_a) + [pivot] + quickSort(lista_b) # Concatenação!

print(quickSort(vet))