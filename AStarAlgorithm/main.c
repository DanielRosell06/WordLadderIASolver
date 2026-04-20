#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "database.h"
#include "node.h"
#include "operations.h"

int main() {

    // Initializing Variables
    printf("Iniciando variáveis!\n");

    int targetIndex;
    int initialIndex;

    printf("Digite o targetIndex: ");
    scanf("%d", &targetIndex);

    printf("Digite o initialIndex: ");
    scanf("%d", &initialIndex);

    ListNode* openList = NULL;
    ListNode* closedList = NULL;
    
    int initialHeuristicFun = heuristicFun(VALID_GUESSES[initialIndex], VALID_GUESSES[targetIndex]);
    Node* currentNode = create_node(initialIndex, 0, initialHeuristicFun, NULL);

    openList = add_to_list(openList, currentNode);
    closedList = add_to_list(closedList, currentNode);

    const char* targetWord = VALID_GUESSES[targetIndex];
    const char* initialWord = VALID_GUESSES[initialIndex];

    // While the indexes arent equal it searchs
    printf("Iniciando comparacoes\n");
    while(openList != NULL && currentNode->index != targetIndex){
        // Comparing with neighbor nodes
        for (int i = 0; i < GRAFO_ROWS; i++) {

            int value = GRAFO[currentNode->index][i];
            // Adding to open list
            if(value == 1 && !is_in_list(closedList, i) && !is_in_list(openList, i)) {
                int hValue = heuristicFun(VALID_GUESSES[targetIndex], VALID_GUESSES[i]);
                Node* newNode = create_node(i, currentNode->cost + 1, hValue, currentNode);
                openList = add_to_list(openList, newNode);
                printf("Adicionando o no %d a lista\n", newNode->index);
            }
        }
        
        // Adding best node to closed list
        Node* nodeData = openList->node;
        openList = remove_from_list(openList);
        currentNode = create_node(nodeData->index, nodeData->cost, nodeData->heuristic, nodeData->parent);
        closedList = add_to_list(closedList, currentNode);
        printf("FINALIZACAO DO PRIMEIRO NO: %d adicionado a lista fechada\n", currentNode->index);
    }

    // Mostrando o caminho
    while(currentNode != NULL) {
        printf("<-");
        printf("%s", VALID_GUESSES[currentNode->index]);
        Node* staticCurrentNode = currentNode;
        currentNode = currentNode->parent;
        free(staticCurrentNode);
    }

    return 0;
}