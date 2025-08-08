lista2 = [10, 11]
def iterator():
    for x in lista2:
        yield x # Return/ponteiros

def main():
    x = 10
    print(f"Numero {x}")

    lista = []
    lista.append(10)

    lista += [30, 12]

    # Iteradores
    for num in lista:
        print(num)

    # Mapa/Dicionário
    dicionario = {}
    dicionario[(1, 2, 3)] = "batata"

    # Lambda
    lista.sort(key = lambda a,b: a < b)

if __name__ == "__main__":
    main()