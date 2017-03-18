#include "stdafx.h"


double RandomDouble(double a, double b)
{
    double random = ((double)rand()) / (double)RAND_MAX;
    double diff = b - a;
    double r = random * diff;
    return a + r;
}


double RandomInt(int a, int b)
{
    int diff = b - a;
    int random = rand() % diff + rand() % 1;
    return a + random;
}