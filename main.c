#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node* create_node(int value);
void print_list(struct Node *head);
struct Node* insert_at_beginning(struct Node *head, int value);
struct Node* insert_at_end(struct Node *head, int value);
struct Node* delete_node(struct Node *head, int value);
int search_node(struct Node *head, int value);

int main()
{
    struct Node *first = create_node(5);
    struct Node *second = create_node(10);
    struct Node *third = create_node(15);

    first->next = second;
    second->next = third;

    first = insert_at_beginning(first, 2);
    print_list(first);

    first = insert_at_end(first, 20);
    print_list(first);

    first = delete_node(first, 10);
    print_list(first);
 
    int pos = search_node(first, 15);
    if(pos != -1) 
    {
        printf("Found 15 at position %d\n", pos);
    }
    else 
    {
        printf("15 not found\n");
    }

    return 0;
}
struct Node* create_node(int value)
{
    struct Node *new_node = malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void print_list(struct Node *head)
{
    struct Node *current = head;

    while(current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

struct Node* insert_at_beginning(struct Node *head, int value)
{
    struct Node *new_node = create_node(value);

    new_node->next = head;
    head = new_node;
    
    return head;
}

struct Node* insert_at_end(struct Node *head, int value)
{
    struct Node *new_node = create_node(value);

    if(head == NULL)
    {
        return new_node;
    }

    struct Node *current = head;

    while(current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_node;
    return head;
}

struct Node* delete_node(struct Node *head, int value)
{
    if(head == NULL)
    {
        return NULL;
    }

    if(head->data == value)
    {
        struct Node *temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct Node *current = head;
    while (current->next != NULL && current->next->data != value)
    {
        current = current->next;
    }
    
    if(current->next != NULL)
    {
        struct Node *temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    
    return head;
}

int search_node(struct Node *head, int value)
{
    struct Node *current = head;
    int position = 0;
    
    while(current != NULL)
    {
        if(current->data == value)
        {
            return position;
        }

        current = current->next;
        position++;
    }
    
    return -1;
}
