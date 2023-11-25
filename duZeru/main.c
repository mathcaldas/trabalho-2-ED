#include "utils.h"
#include "exam.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id, age;
    char name[50], cpf[12];
} Patient;

typedef struct {
    int patient_id, duration;
} Device;

typedef struct {
    int patient_id, duration;
} Radiologist;

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

Radiologist *initialize_radiologist() {
    
}

int main() {
    ExamQueue *q_exam = exq_create();

    Device d[5];

    for (int i = 0; i < 5; i++) {
        initialize_device(&d[i]);
    }

    for (int i = 0; i < 43200; i++) {
        if (gen_randint(0, 100) <= 20){
            Patient *p = create_patient();

            exq_enqueue(q_exam, p->id);
        }

        for (int j = 0; j < 5; j++) {
            if (!exq_is_empty(q) && is_device_available(&d[j])) {
                int patient_id = exq_dequeue(q_exam);
                use_device(&d[j], patient_id);
                continue;
            }
            else if (!is_device_available(&d[j]) && --d[j].duration == 0) {
                // Adicionar para fila para laudo
                int patient_id = d[j].patient_id;
                
            }
                
        }
    }

    return 0;
}