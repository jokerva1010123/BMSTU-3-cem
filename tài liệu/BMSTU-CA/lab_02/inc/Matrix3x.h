#ifndef MATRIX3X_H
#define MATRIX3X_H

#include <vector>
#include <iostream>

#include "Matrix.h"

using namespace std;

class Matrix3x
{
private:
    vector<Matrix> mtr_vec;
public:
    Matrix3x();
    void InputMatrix(const char *file_name);
    const Matrix& operator[](int i) const;
    int get_z();
};

#endif
