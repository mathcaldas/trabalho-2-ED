#include "patient.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct patient {
    int id, age;
    char name[50], cpf[12];
};

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

int get_patient_id(Patient *p) {
    return p->id;
}
