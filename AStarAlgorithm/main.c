#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "database.h"
#include "node.h"
#include "operations.h"

int main() {

    // Initializing Variables
    printf("Iniciando variáveis!\n");

    char initialWord[6];
    char targetWord[6];
    
    printf("Digite a palavra inicial: ");
    scanf("%5s", initialWord);

    printf("Digite a palavra final: ");
    scanf("%5s", targetWord);

    int targetIndex = searchForWord(targetWord);
    if (targetIndex == -1) {
        printf("ERRO: A palavra digitada não existe no banco de dados");
        return 1;
    }

    int initialIndex = searchForWord(initialWord);
    if (initialIndex == -1) {
        printf("ERRO: A palavra digitada não existe no banco de dados");
        return 1;
    }

    int nIteracao = 0;

    ListNode* openList = NULL;
    ListNode* closedList = NULL;
    
    int initialHeuristicFun = heuristicFun(VALID_GUESSES[initialIndex], VALID_GUESSES[targetIndex]);
    Node* currentNode = create_node(initialIndex, 0, initialHeuristicFun, NULL);

    openList = add_to_list(openList, currentNode);
    closedList = add_to_list(closedList, currentNode);

    // While the indexes arent equal it searchs
    printf("Iniciando comparacoes...\n");
    while(openList != NULL && currentNode->index != targetIndex){
        // Comparing with neighbor nodes
        for (int i = 0; i < GRAFO_ROWS; i++) {

            int value = GRAFO[currentNode->index][i];
            // Adding to open list
            if(value == 1 &&  !is_in_list(closedList, i)) {
                float newCost = currentNode->cost + 1;
                if (!is_in_list(openList, i)){
                    int hValue = heuristicFun(VALID_GUESSES[targetIndex], VALID_GUESSES[i]);
                    Node* newNode = create_node(i, newCost, hValue, currentNode);
                    openList = add_to_list(openList, newNode);
                } else {
                    Node* existingNode = get_node_from_list(openList, i);
                    if (newCost < existingNode->cost) {
                        openList = remove_node_by_index(openList, i);
                        existingNode->cost = newCost;
                        existingNode->final = newCost + existingNode->heuristic;
                        existingNode->parent = currentNode;
                        openList = add_to_list(openList, existingNode);
                    }
                }
            }
        }
        
        // Adding best node to closed list
        Node* nodeData = openList->node;
        openList = remove_from_list(openList);
        currentNode = create_node(nodeData->index, nodeData->cost, nodeData->heuristic, nodeData->parent);
        closedList = add_to_list(closedList, currentNode);

        printf("Iteração: %d\n", nIteracao);
        printf("Lista Aberta: ");
        ListNode* tempOpen = openList;
        while(tempOpen != NULL) {
            printf("%s, ", VALID_GUESSES[tempOpen->node->index]);
            tempOpen = tempOpen->next;
        }
        printf("\n");

        printf("Lista Fechada: ");
        ListNode* tempClosed = closedList;
        while(tempClosed != NULL) {
            printf("%s, ", VALID_GUESSES[tempClosed->node->index]);
            tempClosed = tempClosed->next;
        }
        printf("\n\n");
    }

    // Mostrando o caminho
    while(currentNode != NULL) {
        printf("%s", VALID_GUESSES[currentNode->index]);
        if(currentNode->parent != NULL) {
            printf(" <- ");
        }
        Node* staticCurrentNode = currentNode;
        currentNode = currentNode->parent;
        free(staticCurrentNode);
    }

    printf("\n");
    return 0;
}