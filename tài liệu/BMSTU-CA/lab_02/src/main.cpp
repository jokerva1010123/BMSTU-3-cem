#include <iostream>

#include "Menu.h"
#include "interpolate.h"
#include "CppConsoleTable.hpp"
#include "Matrix3x.h"

using ConsoleTable = samilton::ConsoleTable;
using namespace std;

void newton_table();

void newton_param();

Matrix3x table;


int main()
{
//    table.InputMatrix("data.txt");
//    double res = interpolate3x(table, 1.01, 1.01, 0, 3, 3, 3);
//    cout << res;
    try
    {
        table.InputMatrix("data.txt");
        Menu menu(true);
        menu.AddItem(MenuItem("Interpolation", &newton_table));
        menu.AddItem(MenuItem("Interpolation with arbitrary degrees", &newton_param));
        menu.show();
    }
    catch (Error &e)
    {
        e.print_message();
    }

    return 0;
}

void newton_table()
{
    try
    {
        double x = 0, y = 0, z = 0;
        prompt_input("Input x: ", x);
        prompt_input("Input y: ", y);
        prompt_input("Input z: ", z);
        ConsoleTable tb;
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
        tb[0][0] = "Degree";
        tb[0][1] = "Result";

        for (int i = 1; i < 4; i++)
        {
            double res = interpolate3x(table, x, y, z, i, i, i);
            tb[i][0] = i;
            tb[i][1] = res;
        }
        cout << tb;
    }
    catch (Error &e)
    {
        e.print_message();
    }
}

void newton_param()
{
    try
    {
        double x = 0, y = 0, z = 0;
        int nx = 0, ny = 0, nz = 0;
        prompt_input("Input x:", x);
        prompt_input("Input y:", y);
        prompt_input("Input z:", z);
        prompt_input("Input nx:", nx);
        prompt_input("Input ny:", ny);
        prompt_input("Input nz:", ny);
        double res = interpolate3x(table, x, y, z, nx, ny, nz);
        prompt_print("Result: ", res);
    }
    catch (Error &e)
    {
        e.print_message();
    }
}