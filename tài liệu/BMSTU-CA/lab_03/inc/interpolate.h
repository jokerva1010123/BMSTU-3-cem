#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <vector>

#include "MyErrors.h"
#include "Matrix.h"

typedef struct
{
    double a, b, c, d;
} spline_t;

double spline_interp(Matrix &table, double x, bool left, bool right);

double newton_interp(Matrix &table, double x, int n);

#endif 
