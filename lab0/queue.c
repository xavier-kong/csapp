/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>

/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;
    /* What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    if (q != NULL) {
        list_ele_t *head = q->head;

        while (head != NULL) {
            list_ele_t *tmp = head;
            head = head->next;
            free(tmp->value);
            free(tmp);
        }
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

list_ele_t *create_node(queue_t *q, const char *s) {
    if (q == NULL)
        return NULL;

    list_ele_t *node;

    node = malloc(sizeof(list_ele_t));
    if (node == NULL)
        return NULL;

    node->value = malloc(strlen(s) + 1);
    if (node->value == NULL)
        return NULL;

    strcpy(node->value, s);

    return node;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    /*[> What should you do if the q is NULL? <]
    if (q == NULL) return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) return false;

    [> Don't forget to allocate space for the string and copy it <]
    newh->value = malloc(strlen(s) + 1);

    if (newh->value == NULL) return false;
    strcpy(newh->value, s);*/
    list_ele_t *newh = create_node(q, s);

    if (newh == NULL)
        return false;

    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size += 1;

    if (q->size == 1) {
        q->tail = newh;
    }

    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt = create_node(q, s);

    if (newt == NULL)
        return false;

    // new tail next points to null
    newt->next = NULL;

    // old tail
    //
    if (q->size == 0) {
        q->head = newt;
    }

    list_ele_t *oldT = q->tail;

    // old tail (2nd last) next now points to new tail
    oldT->next = newt;

    // current tail for q is now the newly created node
    q->tail = newt;
    q->size += 1;

    if (q->size == 1) {
        q->head = newt;
    }

    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    /* You need to fix up this code. */
    if (q == NULL)
        return false;
    list_ele_t *temp = q->head;

    q->head = q->head->next;

    if (buf != NULL) {
        strncpy(buf, temp->value, bufsize - 2);
        buf[bufsize - 1] = '\0';
        /*char *string = malloc(bufsize);
        for (unsigned long i = 0; i < bufsize - 1; i++) {
            if (i < strlen(temp->value) && temp->value[i]) {
                string[i] = temp->value[i];
            }
        }

        string[bufsize] = '\0';

        strcpy(buf, string);*/
    }

    free(temp->value);
    free(temp);

    q->size -= 1;
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL || q->size == 0)
        return 0;
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */

    list_ele_t *newT = q->head;

    list_ele_t *newH;

    list_ele_t *curr = q->head;

    list_ele_t *prev = NULL;

    while (curr != NULL) {
        newH = curr;

        list_ele_t *temp = curr->next;

        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    q->head = newH;
    q->tail = newT;
}
