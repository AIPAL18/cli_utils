#ifndef CLI_UTILS_LL
#define CLI_UTILS_LL

#include <stdio.h>
#include <stdlib.h>

#include "arg.h"

// https://www.learn-c.org/en/Linked_lists

typedef struct inner_kwarg_node {
    KWArg* val;
    struct inner_kwarg_node * next;
} KWArg_ll;

typedef struct inner_arg_node {
    Arg* val;
    struct inner_arg_node * next;
} Arg_ll;

typedef struct inner_flag_node {
    Flag* val;
    struct inner_flag_node * next;
} Flag_ll;

#define default_head ((void*)0)

void print_list_kwarg(KWArg_ll * head) {
    KWArg_ll * current = head;

    printf("[ ");

    while (current != NULL) {
        printf("\"%s\" ", current->val->name);
        current = current->next;
    }
    
    printf("]\n");
}
void print_list_arg(Arg_ll * head) {
    Arg_ll * current = head;

    printf("[ ");

    while (current != NULL) {
        printf("\"%s\" ", current->val->name);
        current = current->next;
    }
    
    printf("]\n");
}
void print_list_flag(Flag_ll * head) {
    Flag_ll * current = head;

    printf("[ ");

    while (current != NULL) {
        printf("\"%s\" ", current->val->name);
        current = current->next;
    }
    
    printf("]\n");
}

void pushr_kwarg(KWArg_ll **head, KWArg* val) {
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

    // now we can add a new variable 
    current->next = (KWArg_ll *) malloc(sizeof(KWArg_ll));
    current->next->val = val;
    current->next->next = NULL;
}
void pushr_arg(Arg_ll **head, Arg* val) {
if (*head == NULL) {
        *head = (Arg_ll*)malloc(sizeof(Arg_ll));
        (*head)->val = val;
        (*head)->next = NULL;
        return;
    }

    Arg_ll * current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // now we can add a new variable 
    current->next = (Arg_ll *) malloc(sizeof(Arg_ll));
    current->next->val = val;
    current->next->next = NULL;
}
void pushr_flag(Flag_ll **head, Flag* val) {
if (*head == NULL) {
        *head = (Flag_ll*)malloc(sizeof(Flag_ll));
        (*head)->val = val;
        (*head)->next = NULL;
        return;
    }

    Flag_ll * current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // now we can add a new variable 
    current->next = (Flag_ll *) malloc(sizeof(Flag_ll));
    current->next->val = val;
    current->next->next = NULL;
}

void pushl_kwarg(KWArg_ll ** head, KWArg* val) {
    KWArg_ll * new_node;
    new_node = (KWArg_ll *) malloc(sizeof(KWArg_ll));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}
void pushl_arg(Arg_ll ** head, Arg* val) {
    Arg_ll * new_node;
    new_node = (Arg_ll *) malloc(sizeof(Arg_ll));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}
void pushl_flag(Flag_ll ** head, Flag* val) {
    Flag_ll * new_node;
    new_node = (Flag_ll *) malloc(sizeof(Flag_ll));

    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

KWArg* pop_kwarg(KWArg_ll ** head) {
    KWArg* retval = NULL;
    KWArg_ll * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}
Arg* pop_arg(Arg_ll ** head) {
    Arg* retval = NULL;
    Arg_ll * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}
Flag* pop_flag(Flag_ll ** head) {
    Flag* retval = NULL;
    Flag_ll * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}

void free_list_kwarg(KWArg_ll * head) {
    KWArg_ll * current = head;
    KWArg_ll * next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void free_list_arg(Arg_ll * head) {
    Arg_ll * current = head;
    Arg_ll * next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void free_list_flag(Flag_ll * head) {
    Flag_ll * current = head;
    Flag_ll * next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

/*

KWArg* remove_last_kwarg(KWArg_ll * head) {
    KWArg* retval = NULL;
    // if there is only one item in the list, remove it
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    //  get to the second to last node in the list 
    KWArg_ll * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    //  now current points to the second to last item of the list, so let's remove current->next 
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}
Arg* remove_last_arg(Arg_ll * head) {
    Arg* retval = NULL;
    //  if there is only one item in the list, remove it 
    if (head->next == NULL) {
        retval = head->val;
        free(head);
        return retval;
    }

    //  get to the second to last node in the list 
    Arg_ll * current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    //  now current points to the second to last item of the list, so let's remove current->next 
    retval = current->next->val;
    free(current->next);
    current->next = NULL;
    return retval;
}

KWArg* remove_by_index_kwarg(KWArg_ll ** head, int n) {
    int i = 0;
    KWArg* retval = NULL;
    KWArg_ll * current = *head;
    KWArg_ll * temp_node = NULL;

    if (n == 0) {
        return pop_kwarg(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return NULL;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}
Arg* remove_by_index_arg(Arg_ll ** head, int n) {
    int i = 0;
    Arg* retval = NULL;
    Arg_ll * current = *head;
    Arg_ll * temp_node = NULL;

    if (n == 0) {
        return pop_arg(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return NULL;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        return NULL;
    }

    temp_node = current->next;
    retval = temp_node->val;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}

*/

#endif // CLI_UTILS_LL