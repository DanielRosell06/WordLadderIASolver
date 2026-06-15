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
        printf("ERRO: A palavra objetivo não existe no banco de dados");
        return 1;
    }

    int initialIndex = searchForWord(initialWord);
    if (initialIndex == -1) {
        printf("ERRO: A palavra inicial não existe no banco de dados");
        return 1;
    }

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

        printf("Nó expandido: %s (g:%.0f, h:%.0f, f:%.0f)\n", VALID_GUESSES[currentNode->index], currentNode->cost, currentNode->heuristic, currentNode->final);

        ListNode* printNode = openList;
        printf("Lista aberta: [");
        while(printNode != NULL) {
            printf("%s(f:%.0f)", VALID_GUESSES[printNode->node->index], printNode->node->final);
            if(printNode->next != NULL) {
                printf(", ");
            }
            printNode = printNode->next;
        }
        printf("]\n");

        printNode = closedList;
        printf("Lista fechada: [");
        while(printNode != NULL) {
            printf("%s(f:%.0f)", VALID_GUESSES[printNode->node->index], printNode->node->final);
            if(printNode->next != NULL) {
                printf(", ");
            }
            printNode = printNode->next;
        }
        printf("]\n\n\n\n");
        
        // Adding best node to closed list
        Node* nodeData = openList->node;
        openList = remove_from_list(openList);
        currentNode = create_node(nodeData->index, nodeData->cost, nodeData->heuristic, nodeData->parent);
        closedList = add_to_list(closedList, currentNode);
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