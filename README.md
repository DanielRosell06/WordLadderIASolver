# Termo Graph Analysis - Parte 1

Este projeto tem como objetivo analisar a estrutura das palavras do jogo **Termo** (versão brasileira do Wordle) através da teoria dos grafos. 

Esta é a **Parte 1** do projeto, focada na extração dos dados e na construção da matriz de adjacência/grafo de similaridade entre as palavras.

## 📊 O Grafo
No grafo gerado, cada **nó** representa uma palavra de 5 letras da língua portuguesa. Uma **aresta** (conexão) é criada entre duas palavras se elas possuem exatamente **4 letras na mesma posição** (ex: "ababa" e "abaca").

## 🗄️ Base de Dados
A base de dados de palavras (`database.py`) foi obtida a partir do repositório público:
- **Fonte:** [termooo-solver](https://github.com/vgarciasc/termooo-solver)
- **Autor:** [vgarciasc](https://github.com/vgarciasc)

A lista contém aproximadamente 10.589 palavras validadas para o jogo.

## 🚀 Como funciona
1. O script `CreateGrafo.py` lê as palavras da base de dados.
2. Compara cada palavra com todas as outras da lista.
3. Gera um arquivo de grafo que pode ser importado em ferramentas de análise como o **Gephi**.

## ⚠️ Observação sobre arquivos grandes
O arquivo de matriz resultante (`grafo_result.txt`) possui mais de 200MB devido ao volume de combinações ($10.589^2$) e por isso não é incluído no repositório. O script deve ser executado localmente para gerar os dados.

---
*Este projeto é para fins de estudo de ciência de dados e algoritmos.*
