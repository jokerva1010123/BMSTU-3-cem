#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <cmath>

#include "MyErrors.h"
#include "CppConsoleTable.hpp"

#define EPS 1e-4

using namespace std;
using namespace samilton;

class Matrix
{
private:
    int n, m;
    double **table = nullptr;
    void alloc(int n_s, int m_s);
    void free();
    int is_index_valid(int i) const;
public:
    Matrix();
    Matrix(int n, int m);
    Matrix(int n);
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix&);
    void InputMatrix(const char *file_name);
    double* operator[](int i) const;
    int get_n() const;
    int get_m() const;
    void sort();
    void print(const char *message = "");
    ~Matrix();
};

#endif 
