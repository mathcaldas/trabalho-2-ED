#include "report.h" // Include the header file for the ReQueue data structure
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct re_queue
{
   int n;     // Current number of elements in the queue
   int n_max; // Maximum capacity of the queue
   int front; // Index of the front element
   Report **v;  // Vector to store the queue elements
};

struct report {
    int patient_id, initilization;
    Condition condition;
};

// Function to create a new dynamic queue
ReQueue *re_create()
{
   ReQueue *q = (ReQueue *)malloc(sizeof(ReQueue)); // Allocate memory for the ReQueue structure

   q->n = 0;                                         // Initialize the number of elements to 0
   q->n_max = 4;                                     // Allocate initially space for 4 elements
   q->v = (Report **)malloc(q->n_max * sizeof(Report *)); // Allocate memory for the vector data
   q->front = 0;

   return q; // Return a pointer to the created dynamic queue
}

// Helper function to reallocate memory for the dynamic vector
static void reallocate(ReQueue *q)
{
   q->n_max *= 2;                                           // Double the capacity
   q->v = (Report **)realloc(q->v, q->n_max * sizeof(Report *)); // Reallocate memory for the vector data
}

static Condition gen_condition () {
    int prob = gen_randint(0, 100);
    if (prob <= 30)
        return HEALTHY;
    if (prob <= 50)
        return BRONCHITIS;
    if (prob <= 70)
        return PNEUMONIA;
    if (prob <= 85)
        return FEMUR_FRACTURE;
    else
        return APPENDICITIS;
}

static Report *re_create_element(int patient_id, int initialization) {
   Report *v = malloc(sizeof(Report));
   v->patient_id = patient_id;
   v->initilization = initialization;
   v->condition = gen_condition();
   return v;
}

// Function to enqueue an element into the queue
void re_enqueue(ReQueue *q, int patient_id, int initialization)
{
   Report *v = re_create_element(patient_id, initialization);

   if (q->n == q->n_max)
   {
      reallocate(q); // Resize the vector if it is full

      // Shift elements to make space for the new element
      if (q->front != 0)
      {
         memmove(
             &q->v[q->n_max - q->n + q->front], // destination
             &q->v[q->front],                   // source
             (q->n - q->front) * sizeof(Report *)  // bytes to shift
         );
         q->front = q->n_max - q->n + q->front;
      }
   }
   int rear = (q->front + q->n) % q->n_max;
   q->v[rear] = v;
   q->n++;
}

// Function to dequeue an element from the front of the queue
Report *re_dequeue(ReQueue *q)
{
   Report *v = q->v[q->front];
   q->front = (q->front + 1) % q->n_max;
   q->n--;
   return v;
}

// Function to check if the queue is empty
int re_is_empty(ReQueue *q)
{
   return (q->n == 0);
}

int re_get_patient_id(Report *v) {
   return v->patient_id;
}

void re_free_element(Report *v) {
   free(v);
}

// Function to free the memory allocated for the queue
void re_free(ReQueue *q)
{
   for (int i=0; i < q->n; i++) {
      re_free_element(re_dequeue(q));
   }
   free(q->v); // Free the data vector
   free(q);    // Free the ADT
}

void re_print(ReQueue *q)
{
   printf("Size: %d\n", q->n);
   printf("Capacity: %d\n", q->n_max);
   printf("Front: %d \t Rear: %d\n", q->front, (q->front + q->n) % q->n_max);
   printf("Data: ");
   for (int i = 0; i < q->n; i++)
   {
      printf("%d ", q->v[(q->front + i) % q->n_max]->patient_id);
   }
   printf("\n");
}