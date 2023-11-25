#include "utils.h"
#include <stdlib.h>

int gen_randint(int a, int b) {
    return a + rand()%(b - a + 1);
}

int get_qtime_to_exam(int iteration, int initialization){
    return iteration - initialization;
}