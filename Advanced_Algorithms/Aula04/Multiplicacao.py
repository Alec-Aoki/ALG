numeros = [-1, -5, -3, 4, 2, 1]

numeros.sort(key = lambda x: -x) # Ordem decrescente

maiores_positivos = numeros[0] * numeros[1] * numeros[2]
dois_menores_negativos_mair_positivo = numeros[0] * numeros[-1] * numeros[-2]

res = maiores_positivos if maiores_positivos > dois_menores_negativos_mair_positivo else dois_menores_negativos_mair_positivo

print(res)