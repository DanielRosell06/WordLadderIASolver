#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

ListNode* create_list_node(Node* node, ListNode* next) {
    ListNode* new_list_node = (ListNode*)malloc(sizeof(ListNode));
    if (new_list_node != NULL) {
        new_list_node->node = node;
        new_list_node->next = next;
    }
    return new_list_node;
}

Node* create_node(int index, float cost, float heuristic, Node *parent) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    
    if (new_node != NULL) {
        new_node->index = index;
        new_node->cost = cost;
        new_node->heuristic = heuristic;
        new_node->final = cost + heuristic;
        new_node->parent = parent;
    }
    return new_node;
}

ListNode* add_to_list(ListNode* listNode, Node* node) {
    if (listNode == NULL || node->final < listNode->node->final) {
        return create_list_node(node, listNode);
    }

    ListNode* current = listNode;
    while (current->next != NULL && node->final >= current->next->node->final) {
        current = current->next;
    }

    ListNode* newListNode = create_list_node(node, current->next);
    current->next = newListNode;
    return listNode;
}

ListNode* remove_from_list(ListNode* list) {
    if (list == NULL) {
        return NULL;
    }

    ListNode* nextNode = list->next;
    free(list);
    return nextNode;
}

bool is_in_list(ListNode* list, int index) {
    if (list == NULL) {
        return false;
    }

    while(list != NULL) {
        if (list->node->index == index) {
            return true;
        } 
        list = list->next;
    }

    return false;
}