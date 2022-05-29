#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "MyErrors.h"
#include "Matrix.h"

double newton_interp(Matrix &table, double x, int n);

double hermit_interp(Matrix &table, double x, int n, int d);

#endif 
