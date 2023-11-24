#include "utils.h"
#include <stdlib.h>

int gen_randint(int a, int b) {
    return a + rand()%(b - a + 1);
}