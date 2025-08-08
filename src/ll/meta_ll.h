#ifndef CLI_UTILS_META_LL
#define CLI_UTILS_META_LL

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool str_equal(const char* a, const char* b)
{
    return strcmp(a, b) == 0;
}

#define end_node NULL

/*
NEW_LL must keep element ordered (push, pop, ...), because Arg is positionnal.
*/

#define NEW_LL(type) \
    typedef struct type##_inner { \
        type* val; \
        struct type##_inner* next; \
    } type##_ll; \
    type##_ll* type##_ll_new() { \
        return end_node; \
    } \
    void type##_ll_display(type##_ll* head) { \
        type##_ll* current = head; \
        printf("<"); \
        while (current != end_node) { \
            printf("\"%s\" ", current->val->name); \
            current = current->next; \
        } \
        printf("\b]\n"); \
    } \
    void type##_ll_push(type##_ll** head, type* val) { \
        type##_ll * new_node; \
        new_node = malloc(sizeof(type##_ll)); \
        new_node->val = val; \
        new_node->next = *head; \
        *head = new_node; \
    } \
    type* type##_ll_peek(type##_ll ** head) { \
        if (*head == end_node) { \
            return NULL; \
        } \
        return (*head)->val; \
    } \
    type* type##_ll_pop(type##_ll ** head) { \
        type* retval = NULL; \
        type##_ll * next_node = end_node; \
        if (*head == end_node) { \
            return NULL; \
        } \
        next_node = (*head)->next; \
        retval = (*head)->val; \
        free(*head); \
        *head = next_node; \
        return retval; \
    } \
    void type##_ll_free(type##_ll* head) { \
        type##_ll * current = head; \
        type##_ll * next; \
        while (current != end_node) { \
            next = current->next; \
            free(current); \
            current = next; \
        } \
    } \
    bool type##_ll_empty(type##_ll** head) { \
        return (*head == end_node); \
    } \
    bool type##_ll_last(type##_ll** head) { \
        if (*head == end_node) return false; \
        return (*head)->next == end_node; \
    } \
    size_t type##_ll_len(type##_ll* head) { \
        type##_ll* current = head; \
        size_t len = 0; \
        while (current != end_node) { \
            ++len; \
            current = current->next; \
        } \
        return len; \
    } \
    type##_ll* type##_ll_copy(type##_ll* head) { \
        type##_ll* new_head = end_node; \
        type##_ll* tmp = end_node; \
        type##_ll* current = head; \
        while (current != end_node) { \
            type##_ll_push(&tmp, current->val); \
            current = current->next; \
        } \
        current = tmp; \
        while (current != end_node) { \
            type##_ll_push(&new_head, current->val); \
            current = current->next; \
        } \
        return new_head; \
    } \
    type* type##_ll_pop_by_value(type##_ll ** head, type* value) { \
        if (*head == end_node) return NULL; \
        if (str_equal((*head)->val->name, value->name)) { \
            return type##_ll_pop(head); \
        } \
        type* retval = NULL; \
        type##_ll* current = *head; \
        type##_ll* temp_node = end_node; \
        while (current != end_node && !str_equal(current->val->name, value->name)) { \
            current = current->next; \
        } \
        if (current == end_node) return NULL; \
        temp_node = current->next; \
        retval = temp_node->val; \
        current->next = temp_node->next; \
        free(temp_node); \
        return retval; \
    } \

    /*
    void type##_ll_append(type##_ll** head, type* val) { \
        if (*head == end_node) { \
            *head = (type##_ll*)malloc(sizeof(type##_ll)); \
            (*head)->val = val; \
            (*head)->next = end_node; \
            return; \
        } \
        type##_ll* current = *head; \
        while (current->next != end_node) { \
            current = current->next; \
        } \
        current->next = malloc(sizeof(type##_ll)); \
        current->next->val = val; \
        current->next->next = end_node; \
    } \
    */

#endif // CLI_UTILS_META_LL