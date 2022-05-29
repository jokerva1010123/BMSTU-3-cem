#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include <vector>

#include "MyErrors.h"
#include "Matrix.h"
#include "Matrix3x.h"

double newton_interp(Matrix &table, double x, int n);

double interpolate3x(Matrix3x &xyz_table, double x, double y, double z, int nx, int ny, int nz);

#endif 
