import networkx as nx
from collections import defaultdict
from database import UNACCENTED_VALID_GUESSES
import random

def carregar_palavras_do_database(max_palavras=None, seed=42):
    palavras = UNACCENTED_VALID_GUESSES
    if max_palavras is None or max_palavras >= len(palavras):
        return palavras

    rng = random.Random(seed)
    return sorted(rng.sample(palavras, max_palavras))

def carregar_matriz_adjacencia(caminho='grafo_result.txt'):
    matriz = []
    try:
        with open(caminho, 'r', encoding='utf-8') as f:
            for linha in f:
                valores = [int(x) for x in linha.split()]
                matriz.append(valores)
        return matriz
    except FileNotFoundError:
        print(f'Aviso: arquivo {caminho} não encontrado. Calculando conexões a partir do database.py.')
        return None
    except ValueError:
        print(f'Aviso: arquivo {caminho} contém valores inválidos. Calculando conexões a partir do database.py.')
        return None

def criar_grafo_por_matriz(palavras, matriz):
    G = nx.Graph()
    G.add_nodes_from(palavras)
    n = len(palavras)

    for i in range(n):
        for j in range(i + 1, n):
            if matriz[i][j] == 1:
                G.add_edge(palavras[i], palavras[j])
    return G

def criar_grafo_por_ladder(palavras):
    G = nx.Graph()
    G.add_nodes_from(palavras)
    buckets = defaultdict(list)

    for palavra in palavras:
        for i in range(len(palavra)):
            chave = palavra[:i] + '_' + palavra[i + 1:]
            buckets[chave].append(palavra)

    for grupo in buckets.values():
        if len(grupo) < 2:
            continue
        for i in range(len(grupo)):
            for j in range(i + 1, len(grupo)):
                G.add_edge(grupo[i], grupo[j])

    return G

def exportar_para_gephi(G, nome_arquivo='grafo_word_ladder.gexf'):
    """Exporta o grafo para o formato GEXF, lido nativamente pelo Gephi."""
    print(f'Gerando arquivo para o Gephi (Nós: {G.number_of_nodes()}, Arestas: {G.number_of_edges()})...')
    nx.write_gexf(G, nome_arquivo)
    print(f'✅ Sucesso! Grafo exportado para o arquivo: {nome_arquivo}')
    print('Agora abra o Gephi, vá em Arquivo > Abrir e selecione este arquivo.')

def gerar_grafo_completo(max_palavras=None):
    lista_palavras = carregar_palavras_do_database(max_palavras=max_palavras)
    if not lista_palavras:
        print('Nenhuma palavra encontrada no database.py.')
        return

    matriz = carregar_matriz_adjacencia()
    if matriz and len(matriz) == len(lista_palavras) and all(len(linha) == len(lista_palavras) for linha in matriz):
        print('Criando grafo a partir da matriz de adjacência...')
        G = criar_grafo_por_matriz(lista_palavras, matriz)
    else:
        if matriz:
            print('A matriz de adjacência não corresponde ao número de palavras.')
        print('Calculando conexões por uma letra (Word Ladder)...')
        G = criar_grafo_por_ladder(lista_palavras)

    exportar_para_gephi(G)

if __name__ == '__main__':
    # Passando None para garantir que ele pegue TODAS as 11000 palavras
    gerar_grafo_completo(max_palavras=None)