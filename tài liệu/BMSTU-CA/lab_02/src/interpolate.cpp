#include "interpolate.h"

#define X 0
#define Y 1
#define DX 2

void select_borders(Matrix &table, double x, int n, int &l_i);

double newton_interp(Matrix &table, double x, int n);

double interpolate2x(const Matrix &xy_table, double x, double y, double nx, double ny);

double interpolate3x(Matrix3x &xyz_table, double x, double y, double z, int nx, int ny, int nz)
{
    // select z
    Matrix z_values(xyz_table.get_z(), 1);
    for (int i = 0; i < xyz_table.get_z(); i++)
        z_values[i][0] = xyz_table[i][0][0];
    int left_border_z = 0, z_num_for_interp = nz + 2;
    select_borders(z_values, z, z_num_for_interp, left_border_z);
    //do nz + 1 interp by y
    Matrix interp_table(nz + 1, 2);
    for (int i = 0; i < nz + 1; i++)
    {
        double tmp_res = interpolate2x(xyz_table[left_border_z + i], x, y, nx, ny);
        interp_table[i][0] = xyz_table[left_border_z + i][0][0];
        interp_table[i][1] = tmp_res;
    }
    double res = newton_interp(interp_table, z, nz);
    return res;
}

double interpolate2x(const Matrix &xy_table, double x, double y, double nx, double ny)
{
    // select y
    int y_num = xy_table.get_m() - 1;
    Matrix y_values(y_num, 1);
    for (int i = 0; i < y_num; i++)
        y_values[i][0] = xy_table[i + 1][0];
    int left_border_y = 0, y_num_for_interp = ny + 2;
    select_borders(y_values, y, y_num_for_interp, left_border_y);
    //do ny + 1 interp by y
    left_border_y++;
    int y_num_interp = ny + 1;
    Matrix interp_table(y_num_interp, 2);
    for (int i = 0; i < y_num_interp; i++)
    {
        int x_num = xy_table.get_m() - 1;
        Matrix cur_y_table(x_num, 2);
        for (int j = 0; j < x_num; j++)
        {
            cur_y_table[j][0] = xy_table[0][j + 1];
            cur_y_table[j][1] = xy_table[left_border_y + i][j + 1];
        }
        double tmp_res = newton_interp(cur_y_table, x, nx);
        interp_table[i][0] = xy_table[left_border_y + i][0];
        interp_table[i][1] = tmp_res;
    }
    double res = newton_interp(interp_table, y, ny);
    return res;
}

double newton_interp(Matrix &table, double x, int n)
{
    if (n > table.get_n() - 1) throw MathError("not enough points for interpolation");
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

