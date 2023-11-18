#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct {
    int id, age;
    char name[50], cpf[12];
} Patient;

typedef struct {
    int patient_id, initiation, duration, condition;
} Exam;

int gen_randint(int a, int b) {
    return a + rand()%(b - a + 1);
}

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
    p->id = id;
    p->age = gen_randint(20, 80);
    gen_patient_name(p, gen_randint(4, 8));
    gen_patient_cpf(p);
    id++;
    return p;
}

Exam *create_exam(Patient *p) {
    Exam *e = malloc(sizeof(Exam));
    e->patient_id = p->id;
    return e;
}

void print_patient(Patient *p) {
    printf("ID: %d | CPF: %s | Name: %s | Age: %d\n", p->id, p->cpf, p->name, p->age);
}

int main() {
    Queue *q = q_create();
    for (int i = 0; i < 43200; i++) {
        if (gen_randint(0, 100) <= 20){
            Patient *p = create_patient();

            q_enqueue(q, p->id);
           
        }
    }

    q_print(q);
    return 0;
}