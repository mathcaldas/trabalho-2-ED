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

int req_is_empty(ReportQueue *q);
    
void req_enqueue(ReportQueue *q, int patient_id, int initialization);

Exam *req_dequeue(ReportQueue *q);

int req_get_exam_attributes(Exam *e, int *patient_id, int *initialization);

void req_free(ReportQueue *q);

void req_print(ReportQueue *q);

#endif




