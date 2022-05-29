#include "Matrix3x.h"

Matrix3x::Matrix3x()
{

}

void Matrix3x::InputMatrix(const char *file_name)
{
    ifstream inp;
    try
    {
        inp.open(file_name);
    }
    catch (ifstream::failure &e)
    {
        throw AccessError("Wrong input file");
    }
    int nx, ny, nz;
    inp >> nz >> nx >> ny;
    for (int i = 0; i < nz; i++)
    {
        Matrix tmp(nx, ny);
        for (int j = 0; j < nx; j++)
            for (int k = 0; k < ny; k++)
                inp >> tmp[j][k];
//        tmp.print("========================");
        mtr_vec.push_back(tmp);
    }
}

const Matrix &Matrix3x::operator[](int i) const
{
    return mtr_vec[i];
}

int Matrix3x::get_z()
{
    return mtr_vec.size();
}
