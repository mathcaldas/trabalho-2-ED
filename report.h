#ifndef REPORT_H
#define REPORT_H

typedef struct re_queue ReQueue;
typedef struct report Report;

typedef enum
{
    HEALTHY,
    BRONCHITIS,
    PNEUMONIA,
    FEMUR_FRACTURE,
    APPENDICITIS,
} Condition;

// Function prototypes.

// Creates a new empty queue and returns a pointer to it
ReQueue *re_create();

// Enqueues a float value v into the specified queue q
void re_enqueue(ReQueue *q, int patient_id, int initialization);

// Dequeues and returns a float value from the specified queue q
Report *re_dequeue(ReQueue *q);

// Checks if the specified queue q is empty and returns 1 if true, 0 otherwise
int re_is_empty(ReQueue *q);

int re_get_patient_id(Report *v);

void re_free_element(Report *v);

// Frees the memory associated with the specified queue q
void re_free(ReQueue *q);

// Prints the elements of the specified queue q
void re_print(ReQueue *q);

#endif