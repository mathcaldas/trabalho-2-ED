#include "exam.h" // Include the header file for the ExQueue data structure
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ex_queue
{
   int n;     // Current number of elements in the queue
   int n_max; // Maximum capacity of the queue
   int front; // Index of the front element
   int *v;  // Vector to store the queue elements
};

// Function to create a new dynamic queue
ExQueue *ex_create()
{
   ExQueue *q = (ExQueue *)malloc(sizeof(ExQueue)); // Allocate memory for the ExQueue structure

   q->n = 0;                                         // Initialize the number of elements to 0
   q->n_max = 4;                                     // Allocate initially space for 4 elements
   q->v = (int *)malloc(q->n_max * sizeof(int)); // Allocate memory for the vector data
   q->front = 0;

   return q; // Return a pointer to the created dynamic queue
}

// Helper function to reallocate memory for the dynamic vector
static void reallocate(ExQueue *q)
{
   q->n_max *= 2;                                           // Double the capacity
   q->v = (int *)realloc(q->v, q->n_max * sizeof(int)); // Reallocate memory for the vector data
}

// Function to enqueue an element into the queue
void ex_enqueue(ExQueue *q, int v)
{
   if (q->n == q->n_max)
   {
      reallocate(q); // Resize the vector if it is full
      
      // Shift elements to make space for the new element
      if (q->front != 0)
      {
         memmove(
             &q->v[q->n_max - q->n + q->front], // destination
             &q->v[q->front],                   // source
             (q->n - q->front) * sizeof(int)  // bytes to shift
         );
         q->front = q->n_max - q->n + q->front;
      }
   }
   int rear = (q->front + q->n) % q->n_max;
   q->v[rear] = v;
   q->n++;
}

// Function to dequeue an element from the front of the queue
int ex_dequeue(ExQueue *q)
{
   int v = q->v[q->front];
   q->front = (q->front + 1) % q->n_max;
   q->n--;
   return v;
}

// Function to check if the queue is empty
int ex_is_empty(ExQueue *q)
{
   return (q->n == 0);
}

// Function to free the memory allocated for the queue
void ex_free(ExQueue *q)
{
   free(q->v); // Free the data vector
   free(q);    // Free the ADT
}

void ex_print(ExQueue *q)
{
   printf("Size: %d\n", q->n);
   printf("Capacity: %d\n", q->n_max);
   printf("Front: %d \t Rear: %d\n", q->front, (q->front + q->n) % q->n_max);
   printf("Data: ");
   for (int i = 0; i < q->n; i++)
   {
      printf("%d ", q->v[(q->front + i) % q->n_max]);
   }
   printf("\n");
   printf("Memory: ");
   for (int i = 0; i < q->n_max; i++)
   {
      printf("%d ", q->v[i]);
   }
   printf("\n");
}