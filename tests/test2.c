#include <stdio.h>
#include <stdlib.h>

// https://www.learn-c.org/en/Linked_lists

typedef struct inner_node {
    int val;
    struct inner_node * next;
} KWArg_ll;

void print_list(KWArg_ll * head) {
    KWArg_ll * current = head;

    printf("[ ");

    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    
    printf("]\n");
}

void pushr(KWArg_ll **head, int val) {
if (*head == NULL) {
        *head = (KWArg_ll*)malloc(sizeof(KWArg_ll));
        (*head)->val = val;
        (*head)->next = NULL;
        return;
    }

    KWArg_ll * current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = (KWArg_ll *) malloc(sizeof(KWArg_ll));
    current->next->val = val;
    current->next->next = NULL;
}

void pushl(KWArg_ll ** head, int val) {
    KWArg_ll * new_node;
    new_node = (KWArg_ll *) malloc(sizeof(KWArg_ll));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

int pop(KWArg_ll ** head) {
    int retval = -1;
    KWArg_ll * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

int remove_last(KWArg_ll * head) {
    int retval = 0;
    /* if there is only one item in the list, remove it */
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    /* get to the second to last node in the list */
    KWArg_ll * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    /* now current points to the second to last item of the list, so let's remove current->next */
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;

}

int remove_by_index(KWArg_ll ** head, int n) {
    int i = 0;
    int retval = -1;
    KWArg_ll * current = *head;
    KWArg_ll * temp_node = NULL;

    if (n == 0) {
        return pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return -1;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;

}

void free_list(KWArg_ll * head) {
    KWArg_ll * current = head;
    KWArg_ll * next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

int main(void)
{
    KWArg_ll* head = NULL;
    // head = (KWArg_ll *)malloc(sizeof(KWArg_ll));
    // head->val = 0;

    pushr(&head, 0);
    pushr(&head, 1);
    pushr(&head, 2);
    pushr(&head, 3);
    pushr(&head, 4);
    pushr(&head, 5);

    print_list(head);
    
    free_list(head);
    return 0;
}
