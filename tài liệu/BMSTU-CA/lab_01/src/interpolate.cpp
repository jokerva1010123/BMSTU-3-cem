#include "interpolate.h"

#define X 0
#define Y 1
#define DX 2

void select_borders(Matrix &table, double x, int n, int &l_i);

double newton_interp(Matrix &table, double x, int n)
{
    if (n > table.get_n() - 1) throw MathError("not enough points for interpolation");
//    if (n < 1) throw MathError("Degree can't be less than 1");

    int l_i = 0;
    select_borders(table, x, n + 1, l_i);

    int sz = n;
    Matrix mtr(sz);
    int j = 0;
    for (int i = l_i; i < l_i + n; i++)
        mtr[j++][0] = (table[i + 1][Y] - table[i][Y]) / (table[i + 1][X] - table[i][X]);

    j = 1;
    for (j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            mtr[i][j] = (mtr[i + 1][j - 1] - mtr[i][j - 1]) / (table[l_i + i + j + 1][X] - table[l_i + i][X]);

    double res = table[l_i][Y], mlt = 1;
    for (int i = 0; i < sz; i++)
    {
        mlt *= (x - table[l_i + i][X]);
        res += mtr[0][i] * mlt;
    }
    return res;
}

double hermit_interp(Matrix &table, double x, int n, int d)
{
    if (n > table.get_n()) throw MathError("not enough points for interpolation");
//    if (n < 2) throw MathError("Num of points can't be less than 2");

    int l_i = 0;
    select_borders(table, x, n, l_i);

    int sz = (d + 1) * n - 1;
    Matrix mtr(sz);
    int j = 0;
    for (int i = l_i; i < l_i + n; i++)
    {
        for (int k = 0; k < d; k++)
            mtr[j++][0] = table[i][DX + k];
        if(j < sz) mtr[j++][0] = (table[i + 1][Y] - table[i][Y]) / (table[i + 1][X] - table[i][X]);
    }

    j = 1;
    for (j = 1; j < sz; j++)
        for (int i = 0; i < sz - j; i++)

            mtr[i][j] =
                    (mtr[i + 1][j - 1] - mtr[i][j - 1]) / (table[l_i + i / (d + 1) + (j + 1) / (d + 1)][X] - table[l_i + i / (d + 1)][X]);

    double res = table[l_i][Y], mlt = 1;
    for (int i = 0; i < sz; i++)
    {
        mlt *= (x - table[l_i + (i / (d + 1))][X]);
        res += mtr[0][i] * mlt;
    }
    return res;
}


void select_borders(Matrix &table, double x, int n, int &l_i)
{
    if (x <= table[0][0]) l_i = 0;
    else if (x >= table[table.get_n() - 1][0]) l_i = table.get_n() - n;
    else
    {
        int big_border = 1;
        for (; x > table[big_border][0];)
            big_border++;
        int l_n = n / 2, r_n = n - l_n;
        if (big_border - l_n < 0)
            l_i = 0;
        else if (big_border + r_n > table.get_n())
            l_i = big_border - l_n - (big_border + r_n - table.get_n());
        else l_i = big_border - l_n;
    }
}

