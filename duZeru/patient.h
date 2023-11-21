#ifndef PATIENT_H
#define PATIENT_H

typedef struct patient Patient;

void gen_patient_name(Patient *p, int length);

void gen_patient_cpf(Patient *p);

Patient *create_patient();

int get_patient_id(Patient *p);

#endif