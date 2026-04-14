import csv
from database import UNACCENTED_VALID_GUESSES

def compare(word1, word2):
    value = 0;
    for i in range(5):
        if(word1[i] == word2[i]):
            value += 1;

    if(value == 4):
        return 1
    
    return 0


def createArray():
    meu_array = UNACCENTED_VALID_GUESSES

    
    n = len(meu_array)
    grafo = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(len(meu_array)):
        for j  in range(i, len(meu_array)):
            comp = compare(meu_array[i], meu_array[j])
            grafo[i][j] = comp
            grafo[j][i] = comp
            
    with open('grafo_result.txt', mode='w', encoding='utf-8') as f:
        for linha in grafo:
           
            string_linha = " ".join(map(str, linha))
            f.write(string_linha + "\n")


createArray()



            
            