#ifndef EXAM_H
#define EXAM_H

typedef struct ex_queue ExQueue;

// Function prototypes.

// Creates a new empty queue and returns a pointer to it
ExQueue *ex_create();

// Enqueues a float value v into the specified queue q
void ex_enqueue(ExQueue *q, int patient_id);

// Dequeues and returns a float value from the specified queue q
int ex_dequeue(ExQueue *q);

// Checks if the specified queue q is empty and returns 1 if true, 0 otherwise
int ex_is_empty(ExQueue *q);

// Frees the memory associated with the specified queue q
void ex_free(ExQueue *q);

// Prints the elements of the specified queue q
void ex_print(ExQueue *q);

#endif