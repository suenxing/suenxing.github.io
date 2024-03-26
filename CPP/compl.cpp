#include <stdio.h>
#include <stdlib.h>

typedef struct complex
{
    int rel;
    int ima;
} complex;

void ComplexInit(complex *c, int r, int i)
{
    c->rel = r;
    c->ima = i;
}

complex ComplexPlus(complex z1, complex z2)
{
    complex t;
    t.rel = z1.rel + z2.rel;
    t.ima = z1.ima + z2.ima;
    return t;
}

complex ComplexSub(complex z1, complex z2)
{
    complex t;
    t.rel = z1.rel - z2.rel;
    t.ima = z1.ima - z2.ima;
    return t;
}

complex ComplexMul(complex z1, complex z2)
{
    complex t;
    t.rel = z1.rel * z2.rel - z1.ima * z2.ima;
    t.ima = z1.rel * z2.ima + z1.ima * z2.rel;
    return t;
}

complex ComplexPow(complex z1, int po)
{
    complex t = z1;
    for (int i = 0; i < po; i++)
    {
        t = ComplexMul(t, z1);
    }

    return t;
}

int main()
{
    complex z1;
    ComplexInit(&z1, 3, 2);
    z1 = ComplexPow(z1, 1);
    printf("3+2i -> %d+%di", z1.rel, z1.ima);
    system("pause");
}