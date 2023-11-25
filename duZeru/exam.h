#ifndef EXAM_H
#define EXAM_H

typedef struct exam_queue ExamQueue;
typedef struct exam_queue_node ExamQueueNode;


ExamQueue *exq_create();

int exq_is_empty(ExamQueue *q);

void exq_enqueue(ExamQueue *q, int patient_id);

int exq_dequeue(ExamQueue *q)

void exq_free(ExamQueue *q);

void exq_print(ExamQueue *q);

#endif