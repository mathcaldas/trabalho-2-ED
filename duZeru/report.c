#include "report.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct report_queue{
    ReportQueueNode *front;
    ReportQueueNode *rear;
};

struct report_queue_node {
    Exam *exam;
    ReportQueueNode *next;
};

struct exam {
    int patient_id, initialization;
    Condition condition;
};

ReportQueue *req_create(){
    ReportQueue *r = (ReportQueue *)malloc(sizeof(ReportQueue));
    r->front = r->rear = NULL;
    return r;
}

int req_is_empty(ReportQueue *r){
    return r->front == NULL; 
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

void req_enqueue(ReportQueue *r, int patient_id, int initialization){
    ReportQueueNode *node = (ReportQueueNode *)malloc(sizeof(ReportQueueNode));
    
    node->exam = (Exam*)malloc(sizeof(Exam));
    
    node->exam->patient_id = patient_id;
    node->exam->initialization = initialization;
    node->exam->condition = gen_condition();
    
    node->next = NULL;

    if req_is_empty(r)
        r->front = node; 
    else 
        r->rear->next = node;
    r->rear = node;
}

Exam *req_dequeue(ReportQueue *q) {
    assert(!req_is_empty(q));

    Exam *e = q->front->exam;
    ReportQueueNode *p = q->front;

    if (q->front != q->rear)
        q->front = q->front->next;
    else
        q->front = q->rear = NULL;
    
    free(p);
    return e;
}

void req_free(ReportQueue *q) {
    ReportQueueNode *p = r->front; 
    while (p != NULL){
        ReportQueueNode *t = t->next;
        free(p->exam);
        free(p);
        p = t;
    }
    free(q);
}

void req_print(ReportQueue *q) {
    for (ReportQueueNode *p = q->front; p != NULL; p = p->next)
       printf("%d ", p->exam->patient_id);
    printf("\n");
}