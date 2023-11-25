#ifndef REPORT_H
#define REPORT_H

typedef struct report_queue ReportQueue;
typedef struct report_queue_node ReportQueueNode;
typedef struct exam Exam;

typedef enum {
    HEALTHY,
    BRONCHITIS,
    PNEUMONIA,
    FEMUR_FRACTURE,
    APPENDICITIS,
} Condition;

ReportQueue *req_create();

int req_length(ReportQueue *q);

int req_is_empty(ReportQueue *q);
    
void req_enqueue(ReportQueue *q, int patient_id, int initialization);

Exam *req_dequeue(ReportQueue *q);

void req_get_exam_attributes(Exam *e, int *patient_id, int *initialization, Condition *condition);

void req_clear(ReportQueue *q, int iteration, int limit, int avg_pathology_time[5], int cont_pathology_exams[5]);

void req_free(ReportQueue *q);

void req_print(ReportQueue *q);

char *get_condition_name(Condition condition);

#endif




