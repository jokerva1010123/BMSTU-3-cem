#include "Matrix.h"



void Matrix::alloc(int n, int m)
{
    try
    {
        if (table != nullptr)
            this->free();
        this->n = n;
        this->m = m;
        table = new double *[this->n];
        for (int i = 0; i < n; i++)
            table[i] = new double[this->m];
    }
    catch (bad_alloc  &e)
    {
        throw AllocError("Out of memory");
    }
}

void Matrix::free()
{

    for (int i = 0; i < n; i++)
        delete[] table[i];
    delete table;
    table = nullptr;
}

int Matrix::is_index_valid(int i) const
{
    if (i < 0 || i > n - 1)
        return 0;
    return 1;
}

Matrix::Matrix() : n(0), m(0), table(nullptr)
{}

Matrix::Matrix(int n, int m) : n(n), m(m), table(nullptr)
{
    this->alloc(n, m);
}


Matrix::Matrix(int n) : n(n), m(n), table(nullptr)
{
    this->alloc(n, n);
}
Matrix::Matrix(const Matrix &mtr)
{
    this->alloc(mtr.n, mtr.m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            table[i][j] = mtr[i][j];

}

Matrix &Matrix::operator=(const Matrix &mtr)
{
    if (table != nullptr)
        this->free();
    this->alloc(mtr.n, mtr.n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            table[i][j] = mtr[i][j];
    return *this;
}

void Matrix::InputMatrix(const char *file_name)
{
    if (table != nullptr)
        this->free();
    ifstream inp;
    try
    {
        inp.open(file_name);
    }
    catch (ifstream::failure &e)
    {
        throw AccessError("Wrong input file");
    }
    inp >> n >> m;
    this->alloc(n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            inp >> table[i][j];
    inp.close();
}

double *Matrix::operator[](int i) const
{
    if(table == nullptr)
        throw AccessError("Memory are not allocated");
    if(!this->is_index_valid(i))
        throw AccessError("Out of range");
    return table[i];
}

int Matrix::get_n() const
{
    return n;
}

int Matrix::get_m() const
{
    return m;
}

int cmp(const double *n1, const double *n2);

void Matrix::sort()
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
        {
            if (cmp(table[j], table[j + 1]) > 0)
            {
                double *tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
        }
}

void Matrix::print(const char *message)
{
    ConsoleTable tb(1, 1);
    ConsoleTable::TableChars chars;
    chars.leftRightSimple = '|';
    chars.topDownSimple = '-';
    chars.downLeft = '-';
    chars.topLeft = '-';
    chars.downRight = '-';
    chars.topRight = '-';
    chars.downSeparation = '-';
    chars.topSeparation = '-';
    chars.centreSeparation = '|';
    chars.leftSeparation = '|';
    chars.rightSeparation = '|';
    tb.setTableChars(chars);
    cout << message << endl;
    for (int i = 1; i < m + 1; i++) tb[0][i] = i - 1;
    for (int i = 0; i < n; i++)
    {
        tb[i + 1][0] = i;
        for (int j = 0; j < m; j++)
        {
            tb[i + 1][j + 1] = table[i][j];
        }
    }
    cout << tb;
}

Matrix::~Matrix()
{
    this->free();
}

int cmp(const double *n1, const double *n2)
{
    if (fabs(*n1 - *n2) < EPS)
        return 0;
    if(*n1 - *n2 < 0)
        return -1;
    else
        return 1;
}
