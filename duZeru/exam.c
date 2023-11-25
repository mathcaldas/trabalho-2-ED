#include "exam.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct exam_queue {
    int n;
    ExamQueueNode *front;
    ExamQueueNode *rear;
};

struct exam_queue_node {
    int patient_id;
    ExamQueueNode *next;
};

ExamQueue *exq_create() {
    ExamQueue *q = (ExamQueue *)malloc(sizeof(ExamQueue));
    q->front = q->rear = NULL;
    return q;
}

int exq_length(ExamQueue *q) {
    return q->n;
}

int exq_is_empty(ExamQueue *q) {
    return exq_length(q) == 0;
}

void exq_enqueue(ExamQueue *q, int patient_id) {
    ExamQueueNode *node = (ExamQueueNode *)malloc(sizeof(ExamQueueNode));

    node->patient_id = patient_id;
    node->next = NULL;

    if (exq_is_empty(q))
        q->front = node;
    else
        q->rear->next = node;
    q->rear = node;

    q->n++;
}

int exq_dequeue(ExamQueue *q) {
    assert(!exq_is_empty(q));

    int v = q->front->patient_id;
    ExamQueueNode *p = q->front;

    if(q->front != q->rear)
        q->front = q->front->next;
    else
        q->front = q->rear = NULL;
    
    free(p);

    q->n--;

    return v;
}

void exq_free(ExamQueue *q) {
    ExamQueueNode *p = q->front;

    while (p != NULL) {
        ExamQueueNode *t = p->next;
        free(p);
        p = t;
    }
    free(q);
}

void exq_print(ExamQueue *q) {
    for (ExamQueueNode *p = q->front; p != NULL; p = p->next)
        printf("%d ", p->patient_id);
    printf("\n");
}