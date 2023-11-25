#include "report.h"
#include "utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct report_queue{
    int n;
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
    ReportQueue *q = (ReportQueue *)malloc(sizeof(ReportQueue));
    q->n = 0;
    q->front = q->rear = NULL;
    return q;
}

int req_length(ReportQueue *q) {
    return q->n;
}

int req_is_empty(ReportQueue *q){
    return req_length(q) == 0; 
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

void req_enqueue(ReportQueue *q, int patient_id, int initialization){
    ReportQueueNode *node = (ReportQueueNode *)malloc(sizeof(ReportQueueNode));
    
    node->exam = (Exam*)malloc(sizeof(Exam));
    
    node->exam->patient_id = patient_id;
    node->exam->initialization = initialization;
    node->exam->condition = gen_condition();
    
    node->next = NULL;

    if (req_is_empty(q))
        q->front = node; 
    else 
        q->rear->next = node;
    q->rear = node;

    q->n++;
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

    q->n--;
    return e;
}

void req_get_exam_attributes(Exam *e, int *patient_id, int *initialization, Condition *condition) {
    *patient_id = e->patient_id;
    *initialization = e->initialization;
    *condition = e->condition;
}

void req_clear(ReportQueue *q, int iteration, int limit, int avg_pathology_time[5], int cont_pathology_exams[5]) {
    while (q->front != NULL && iteration - q->front->exam->initialization >= limit) {
        Exam *e = req_dequeue(q);
        avg_pathology_time[e->condition] += limit;
        cont_pathology_exams[e->condition]++;
        free(req_dequeue(q));
        q->n--;
    }
}

void req_free(ReportQueue *q) {
    ReportQueueNode *p = q->front; 
    while (p != NULL){
        ReportQueueNode *t = p->next;
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

char *get_condition_name(Condition condition) {
    switch (condition) {
        case HEALTHY: return "HEALTHY";
        case BRONCHITIS: return "BRONCHITIS";
        case PNEUMONIA: return "PNEUMONIA";
        case FEMUR_FRACTURE: return "FEMUR_FRACTURE";
        case APPENDICITIS: return "APPENDICITIS";
        default: return "INVALID";
    }
} 