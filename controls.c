#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

void melanger()
{
    int i = 0, randomValue = (int)(rand() / (double)RAND_MAX * (25 - 1));
    while (i != randomValue) { shuffle(); i++; }
    printf("r---->%d\n", randomValue);
}