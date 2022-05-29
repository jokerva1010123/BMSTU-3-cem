#include "interpolate.h"

#define X 0
#define Y 1
#define DX 2

void select_borders(Matrix &table, double x, int n, int &l_i);

spline_t *calc_splines_coeffs(Matrix &table, bool left, bool right);

double calc_value_spline(spline_t *splines, Matrix &table, double x);

void forward_move(Matrix &table, double *xee, double *etha, int size, bool is_null);

void back_move(spline_t *splines, Matrix &table, double *xee, double *etha, int size, bool is_null);

double get_left(Matrix &table);

double get_right(Matrix &table);

double newton_interp(Matrix &table, double x, int n)
{
    if (n > table.get_n() - 1) throw MathError("Not enough points for interpolation");
    if (n < 1) throw MathError("Degree can't be less than 1");

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

double spline_interp(Matrix &table, double x, bool left, bool right)
{
    spline_t *splines = calc_splines_coeffs(table, left, right);
    double res = calc_value_spline(splines, table, x);
    free(splines);
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

spline_t *calc_splines_coeffs(Matrix &table, bool left, bool right)
{
    int size = table.get_n();
    auto *splines = static_cast<spline_t *>(malloc((size + 1) * sizeof(spline_t)));

    auto *xee = static_cast<double *>(malloc((size + 1) * sizeof(double)));
    auto *etha = static_cast<double *>(malloc((size + 1) * sizeof(double)));

    if (!xee || !etha || !splines)
    {
        free(xee);
        free(etha);
        free(splines);
        return nullptr;
    }

    forward_move(table, xee, etha, size, left);
    back_move(splines, table, xee, etha, size, right);

    free(etha);
    free(xee);
    return splines;
}

double calc_value_spline(spline_t *splines, Matrix &table, double x)
{
    int size = table.get_n();
    int i;
    for (i = 1; i < size - 1 && x > table[i][X]; i++);

    double y = splines[i].a;
    y += splines[i].b * (x - table[i - 1][X]);
    y += splines[i].c * (x - table[i - 1][X]) * (x - table[i - 1][X]);
    y += splines[i].d * (x - table[i - 1][X]) * (x - table[i - 1][X]) \
 * (x - table[i - 1][X]);

    return y;
}

void forward_move(Matrix &table, double *xee, double *etha, int size, bool is_null)
{
    xee[2] = etha[2] = 0;

    for (int i = 2; i < size; i++)
    {
        double D_i = table[i][X] - table[i - 1][X];
        double B_i = 2 * (table[i - 2][X] - table[i][X]);
        double A_i = table[i - 1][X] - table[i - 2][X];
        double F_i = -3 * ((table[i][Y] - table[i - 1][Y]) / D_i - \
                        (table[i - 1][Y] - table[i - 2][Y]) / A_i);

        xee[i + 1] = D_i / (B_i - A_i * xee[i]);
        etha[i + 1] = (A_i * etha[i] + F_i) / (B_i - A_i * xee[i]);
    }
}

void back_move(spline_t *splines, Matrix &table, double *xee, double *etha, int size, bool is_null)
{
    if (is_null)
        splines[size].c = get_right(table);
    else
        splines[size].c = 0;

    for (int i = size - 1; i >= 1; i--)
    {
        splines[i].c = xee[i + 1] * splines[i + 1].c + etha[i + 1];
        splines[i].a = table[i - 1][Y];
        double h = table[i][X] - table[i - 1][X];
        splines[i].b = (table[i][Y] - table[i - 1][Y]) / h - \
                        h / 3.0 * (2 * splines[i].c + splines[i + 1].c);
        splines[i].d = (splines[i + 1].c - splines[i].c) / h / 3.0;
    }
}

double get_left(Matrix &table)
{
    int n = 4;
    int l_i = 0, sz = n;
    Matrix mtr(sz);
    int j = 0;
    for (int i = l_i; i < l_i + n; i++)
        mtr[j++][0] = (table[i + 1][Y] - table[i][Y]) / (table[i + 1][X] - table[i][X]);

    j = 1;
    for (j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            mtr[i][j] = (mtr[i + 1][j - 1] - mtr[i][j - 1]) / (table[l_i + i + j + 1][X] - table[l_i + i][X]);
    double a = table[0][X], b = table[1][X], c = table[2][X];
    double r4 = mtr[0][sz - 1], r3 = mtr[0][sz - 2];
    double x = table[l_i][X];
    return 2.0 * r4 * (x - c - b - a) + 2.0 * r3;
}

double get_right(Matrix &table)
{
    int n = 4;
    int l_i = table.get_n() - 5, sz = n;
    Matrix mtr(sz);
    int j = 0;
    for (int i = l_i; i < l_i + n; i++)
        mtr[j++][0] = (table[i + 1][Y] - table[i][Y]) / (table[i + 1][X] - table[i][X]);

    j = 1;
    for (j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            mtr[i][j] = (mtr[i + 1][j - 1] - mtr[i][j - 1]) / (table[l_i + i + j + 1][X] - table[l_i + i][X]);
    double a = table[0][X], b = table[1][X], c = table[2][X];
    double r4 = mtr[0][sz - 1], r3 = mtr[0][sz - 2];
    double x = table[l_i][X];
    return 2.0 * r4 * (x - c - b - a) + 2.0 * r3;
}