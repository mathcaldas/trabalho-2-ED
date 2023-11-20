#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "exam.h"
#include "report.h"

typedef struct {
    int id, age;
    char name[50], cpf[12];
} Patient;

struct awaitable {
    int patient_id, duration;
};

typedef struct awaitable Device;
typedef struct awaitable Radiologist;

// Patient

void gen_patient_name(Patient *p, int length) {
    char name[length+1];
    name[0] = gen_randint('A', 'Z');
    for (int i=1; i < length; i++)
        name[i] = gen_randint('a', 'z');
    name[length] = '\0';
    strcpy(p->name, name);
}

void gen_patient_cpf(Patient *p) {
    char cpf[12];
    for (int i=0; i < 11; i++)
        cpf[i] = gen_randint('0', '9');
    cpf[11] = '\0';
    strcpy(p->cpf, cpf);
}

Patient *create_patient() {
    static int id;
    Patient *p = malloc(sizeof(Patient));
    if (p == NULL) {
        printf("No memory.");
        return NULL;
    }
    p->id = id++;
    p->age = gen_randint(20, 80);
    gen_patient_name(p, gen_randint(4, 8));
    gen_patient_cpf(p);
    return p;
}

void print_patient(Patient *p) {
    printf("ID: %d | CPF: %s | Name: %s | Age: %d\n", p->id, p->cpf, p->name, p->age);
}

// Device

Device *add_device() {
    Device *d = malloc(sizeof(Device));
    d->duration = 0;
    return d;
}

void use_device(Device *d, int patient_id) {
    d->patient_id = patient_id;
    d->duration = gen_randint(5, 10);
}

int is_device_available(Device *d) {
    return d->duration == 0;
}

// Radiologist

Radiologist *add_radiologist() {
    Radiologist *r = malloc(sizeof(Radiologist));
    r->duration = 0;
    return r;
}

void attend_radiologist(Radiologist *r, int patient_id) {
    r->patient_id = patient_id;
    r->duration = gen_randint(10, 30);
}

int is_radiologist_available(Radiologist *r) {
    return r->duration == 0;
}

int main() {
    ExQueue *q_exam = ex_create();
    ReQueue *q_report = re_create();
    Device *devices[5];
    Radiologist *radiologists[3];

    for (int i = 0; i < 5; i++) {
        devices[i] = add_device();
    }

    for (int i = 0; i < 3; i++) {
        radiologists[i] = add_radiologist();
    }

    for (int i = 0; i < 40; i++) {
        if (gen_randint(0, 100) <= 20){
            Patient *p = create_patient();
            if (p == NULL)
                return -1;
            ex_enqueue(q_exam, p->id);
        }

        for (int j = 0; j < 5; j++) {
            if (!ex_is_empty(q_exam) && is_device_available(devices[j])) {
                int patient_id = ex_dequeue(q_exam);
                use_device(devices[j], patient_id);
                continue;
            }
            if (!is_device_available(devices[j]) && --devices[j]->duration == 0) {      
                re_enqueue(q_report, devices[j]->patient_id, i);
            }
        }

        for (int j = 0; j < 3; j++) {
            if (!re_is_empty(q_report) && is_radiologist_available(radiologists[j])) {
                Report *r = re_dequeue(q_report);
                attend_radiologist(radiologists[j], re_get_patient_id(r));
                re_free_element(r);
                continue;
            }
            if (!is_radiologist_available(radiologists[j])) {
                radiologists[j]->duration--;
            }
        }
        if (i % 1000 == 0) {
            ex_print(q_exam);
            re_print(q_report);
        }
    }

    for (int i = 0; i < 5; i++) {
        free(devices[i]);
    }

    for (int i = 0; i < 3; i++) {
        free(radiologists[i]);
    }

    ex_free(q_exam);
    re_free(q_report);
    return 0;
}