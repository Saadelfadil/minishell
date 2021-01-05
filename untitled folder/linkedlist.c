#include <stdlib.h>
#include  <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct node_t {
    char *value;
    struct node_t *next;
}node_t;

void print_nodes(node_t **head)
{
    node_t *temporary = *head;

    while (temporary != NULL)
    {
        printf("[%s]", temporary->value);
        temporary = temporary->next;
    }
}

void add_nodes(node_t **head,char *value)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}


void free_nodes(node_t **head)
{
    node_t *temporary = *head;
    node_t *node;

    node = *head;
    while (node != NULL)
    {
        temporary = node;
        node = node->next;
        free(temporary);
        *head = NULL;
    }
}

void push_in_nodes(node_t **head_ref, char *new_data) 
{ 
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	new_node->value = new_data; 
	(*head_ref) = new_node; 
} 

void add_at_the_end(node_t **head_ref, char *new_data, int *i) 
{
    if (*i == 0)
    {
        node_t *new_node = (node_t *)malloc(sizeof(node_t));
        new_node->value = new_data;
	    (*head_ref) = new_node;
        *i = 1;
        return;
    }
    node_t *new_node = (node_t*) malloc(sizeof(node_t));
    node_t *last = *head_ref;
    new_node->value = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }
    while (last->next != NULL) 
        last = last->next;
    last->next = new_node;
}

void romove_nodes(node_t **head, char *value)
{
    node_t *tmp = *head;
    
    node_t *pr = NULL;
    if (strcmp(tmp->value, value) == 0)
    {
        tmp = tmp->next;
        *head = tmp;
    }
    while (tmp != NULL)
    {
        if (strcmp(tmp->value, value) == 0)
        {
            pr->next = tmp->next;
            free(tmp);
        }
        pr = tmp;
        tmp = tmp->next;
    }
}

int main() {
    node_t *head;
    node_t *tmp;
    int i = 0;

    add_at_the_end(&head, "jiji", &i);
    add_at_the_end(&head, "mama", &i);
    add_at_the_end(&head, "baba", &i);
    add_at_the_end(&head, "nina", &i);

    romove_nodes(&head, "saad");
    print_nodes(&head);
    free_nodes(&head);
    print_nodes(&head);
    printf("\nAfter free -> free done");
    return 0;
}