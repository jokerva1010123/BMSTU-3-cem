#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OK 0

double F(double x)
{
    return x * x;
}

int main()
{
    FILE *f = fopen("table.txt", "w");

    double start, stop, step;
    printf("Input Start X, Stop of X, Step X: ");
    scanf("%lf%lf%lf", &start, &stop, &step);

    fprintf(f, "Count %d\n\n", (int)((stop - start) / step) + 1);

    for (double cur = start; cur <= stop; cur += step)
    {
        fprintf(f, "%lf %lf\n", cur, F(cur));
    }

    fclose(f);

    return OK;
}