#include "utils.h"
#include "exam.h"
#include "patient.h"
#include "report.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct awaitable {
    int patient_id, duration;
};

typedef struct awaitable Device;
typedef struct awaitable Radiologist;

// Device

void initialize_device(Device *d) {
    d->duration = 0;
}

void use_device(Device *d, int patient_id) {
    d->patient_id = patient_id;
    d->duration = gen_randint(5, 10);
}

int is_device_available(Device *d){
    return d->duration == 0;
}

// Radiologist

void initialize_radiologist(Radiologist *r) {
    r->duration = 0;
}

void use_radiologist(Radiologist *r, int patient_id) {
    r->patient_id = patient_id;
    r->duration = gen_randint(10, 30);
}

int is_radiologist_avaliable(Radiologist *r){
    if (r->duration == 0)
        return 1;
    return 0;
}

int main() {
    ExamQueue *q_exam = exq_create();
    ReportQueue *q_report = req_create();

    Device d[5];
    Radiologist r[3];

    for (int i = 0; i < 5; i++) {
        initialize_device(&d[i]);
    }

    for (int i = 0; i < 3; i++){
        initialize_radiologist(&r[i]);
    }

    for (int i = 0; i < 43200; i++) {
        if (gen_randint(0, 100) <= 20){
            Patient *p = create_patient();

            exq_enqueue(q_exam, get_patient_id(p));
        }

        for (int j = 0; j < 5; j++) {
            if (!exq_is_empty(q_exam) && is_device_available(&d[j])) {
                int patient_id = exq_dequeue(q_exam);
                use_device(&d[j], patient_id);
                continue;
            }
            else if (!is_device_available(&d[j]) && --d[j].duration == 0) {
                int patient_id = d[j].patient_id;
                
                req_enqueue(q_report, patient_id, i);
            }
        }

        for (int j =0; j<3; j++ ){
            if (!req_is_empty(q_report) && is_radiologist_avaliable(&r[j])){
                Exam *exam;
                int patient_id, initialization;
                do {
                    exam = req_dequeue(q_report);
                    req_get_exam_attributes(exam, &patient_id, &initialization);
                    free(exam);
                } while (i-initialization >= 7200);
                use_radiologist(&r[j], patient_id);
                continue;
            }
            else if (!is_radiologist_avaliable(&r[j])) {
                r[j].duration--;
            }
        }

    }

    exq_print(q_exam);
    req_print(q_report);
    exq_free(q_exam);
    req_free(q_report);
    return 0;
}