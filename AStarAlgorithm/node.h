#ifndef NODE_H
#define NODE_H

typedef struct Node {
    int index;            
    float cost, heuristic, final;       
    struct Node *parent;
} Node;

typedef struct ListNode {
    Node* node;
    struct ListNode* next;
} ListNode;

ListNode* create_list_node(Node* node, ListNode* next);
Node* create_node(int index, float cost, float heuristic, Node *parent);
ListNode* add_to_list(ListNode* listNode, Node* node);
ListNode* remove_from_list(ListNode* list);
bool is_in_list(ListNode* list, int index);

#endif