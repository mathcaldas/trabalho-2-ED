#include "utils.h"
#include "exam.h"
#include "patient.h"
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Q_REPORT_TIME_LIMIT 7200
#define SLEEP_TIME 10000

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

int is_any_device_available(Device d[5]) {
    for (int i=0; i < 5; i++)
        if (is_device_available(&d[i]))
            return 1;
    return 0;
}

// Radiologist

void initialize_radiologist(Radiologist *r) {
    r->duration = 0;
}

void use_radiologist(Radiologist *r, int patient_id) {
    r->patient_id = patient_id;
    r->duration = gen_randint(10, 30);
}

int is_radiologist_available(Radiologist *r){
    if (r->duration == 0)
        return 1;
    return 0;
}

int is_any_radiologist_available(Radiologist r[3]) {
    for (int i=0; i < 3; i++)
        if (is_radiologist_available(&r[i]))
            return 1;
    return 0;
}

int main() {
    ExamQueue *q_exam = exq_create();
    ReportQueue *q_report = req_create();

    Device d[5];
    Radiologist r[3];
    
    int acc_cont_patient_exams, acc_pathology_time;
    float exam_time_result = 0;
    int pathology_exams_time[5] = {0};
    int cont_pathology_exams[5] = {0};
    float avg_pathology_time[5] = {0};

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
        req_clear(q_report, i, Q_REPORT_TIME_LIMIT, pathology_exams_time, cont_pathology_exams);
        for (int j = 0; j < 3; j++){
            if (!req_is_empty(q_report) && is_radiologist_available(&r[j])){
                Condition condition;
                int patient_id, initialization;
                Exam *exam = req_dequeue(q_report);
                req_get_exam_attributes(exam, &patient_id, &initialization, &condition);
                free(exam);
                int queue_time = get_qtime_to_exam(i, initialization);

                pathology_exams_time[condition] += queue_time;
                cont_pathology_exams[condition]++;
                use_radiologist(&r[j], patient_id);

                continue;
            }
            else if (!is_radiologist_available(&r[j])) {
                r[j].duration--;
            }
        }

        if (i % 100 == 0) {
            acc_cont_patient_exams = acc_pathology_time = 0;
            for (int i=HEALTHY; i <= APPENDICITIS; i++) {
                acc_pathology_time += pathology_exams_time[i];
                acc_cont_patient_exams += cont_pathology_exams[i];
                avg_pathology_time[i] = cont_pathology_exams[i] > 0 ? (float)pathology_exams_time[i]/cont_pathology_exams[i] : 0;
            }
            exam_time_result = acc_cont_patient_exams > 0 ? (float)acc_pathology_time/acc_cont_patient_exams : 0;
            printf("Iter %d: Tempo medio: %.2f\nPor condicao: |", i, exam_time_result);
            for (int i=HEALTHY; i <= APPENDICITIS; i++)
                printf(" %s: %.2f |", get_condition_name(i), avg_pathology_time[i]);
            printf("\n");
            usleep(SLEEP_TIME);
        }
    }

    printf("\nGerenciando filas com dados remanescentes: \n");
    const int passed_limit_time = req_length(q_report);

    for (int i = 43200; !exq_is_empty(q_exam) || !req_is_empty(q_report) || !is_any_device_available(d) || !is_any_radiologist_available(r); i++) {
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
        req_clear(q_report, i, Q_REPORT_TIME_LIMIT, pathology_exams_time, cont_pathology_exams);
        for (int j = 0; j < 3; j++){
            if (!req_is_empty(q_report) && is_radiologist_available(&r[j])){
                Condition condition;
                int patient_id, initialization;
                Exam *exam = req_dequeue(q_report);
                req_get_exam_attributes(exam, &patient_id, &initialization, &condition);
                free(exam);
                int queue_time = get_qtime_to_exam(i, initialization);
                
                pathology_exams_time[condition] += queue_time;
                cont_pathology_exams[condition]++;
                use_radiologist(&r[j], patient_id);
                
                continue;
            }
            else if (!is_radiologist_available(&r[j])) {
                r[j].duration--;
            }
        }

        if (i % 100 == 0) {
            acc_cont_patient_exams = acc_pathology_time = 0;
            for (int i=HEALTHY; i <= APPENDICITIS; i++) {
                acc_pathology_time += pathology_exams_time[i];
                acc_cont_patient_exams += cont_pathology_exams[i];
                avg_pathology_time[i] = cont_pathology_exams[i] > 0 ? (float)pathology_exams_time[i]/cont_pathology_exams[i] : 0;
            }
            exam_time_result = acc_cont_patient_exams > 0 ? (float)acc_pathology_time/acc_cont_patient_exams : 0;
            printf("Iter %d: Tempo medio: %.2f\nPor condicao: |", i, exam_time_result);
            for (int i=HEALTHY; i <= APPENDICITIS; i++)
                printf(" %s: %.2f |", get_condition_name(i), avg_pathology_time[i]);
            printf("\n");
            usleep(SLEEP_TIME);
        }
    }

    acc_pathology_time = acc_cont_patient_exams = 0;
    for (int i=HEALTHY; i <= APPENDICITIS; i++) {
        acc_pathology_time += pathology_exams_time[i];
        acc_cont_patient_exams += cont_pathology_exams[i];
        avg_pathology_time[i] = (float)pathology_exams_time[i]/cont_pathology_exams[i];
    }
    
    exam_time_result = (float)acc_pathology_time/acc_cont_patient_exams;

    printf("\nResultado do tempo medio na fila para laudo: %.2f\n\n", exam_time_result);
    
    printf("Resultado do tempo médio por condicao:\n");
    for (int i=HEALTHY; i <= APPENDICITIS; i++)
        printf("%s: %.2f\n", get_condition_name(i), avg_pathology_time[i]);
    printf("\n");
    printf("Pacientes que ultrapassaram o tempo limite: %d\n", passed_limit_time);
    exq_free(q_exam);
    req_free(q_report);
    return 0;
}