#include <iostream>
#include <cmath>

#include "Menu.h"
#include "interpolate.h"
#include "CppConsoleTable.hpp"
#include "Matrix.h"

using ConsoleTable = samilton::ConsoleTable;
using namespace std;

void newton();

void hermit();

void cmp();

void root();

Matrix table;


int main()
{
//    table.InputMatrix("data1.txt");
//    double res = hermit_interp(table, 0.5, 8, 1);

    try
    {
        table.InputMatrix("data1.txt");
        table.sort();
        Menu menu(true);
        menu.AddItem(MenuItem("Use Newton's polynomial", &newton));
        menu.AddItem(MenuItem("Use Hermite's polynomial", &hermit));
        menu.AddItem(MenuItem("Compare polynomials", &cmp));
        menu.AddItem(MenuItem("Find the root", &root));
        menu.show();
    }
    catch (Error &e)
    {
        e.print_message();
    }

    return 0;
}

void newton()
{
    try
    {
        double x = 0;
        prompt_input("Input argument: ", x);
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

        for (int i = 0; i < table.get_n() - 1; i++)
        {
            double res = newton_interp(table, x, i);
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

void hermit()
{
    try
    {
        double x = 0;
        prompt_input("Input argument: ", x);
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
        tb[0][0] = "Dots num";
        tb[0][1] = "Result";

        for (int i = 1; i < table.get_n(); i++)
        {
            double res = hermit_interp(table, x, i, table.get_m() - 2);
            tb[i - 1][0] = i;
            tb[i - 1][1] = res;
        }
        cout << tb;
    }
    catch (Error &e)
    {
        e.print_message();
    }
}

void cmp()
{
    try
    {
        double x = 0;
        prompt_input("Input argument: ", x);
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
        tb[0][0] = "Degree";
        tb[0][1] = "Newton";
        tb[0][2] = "Hermite";
        tb[0][3] = "Absolute diff";
        tb[0][4] = "Relative diff";

        int j = 1;
//        for (int i = 2; i * 2 - 1 < table.get_n() - 1; i++)
//        {
//            double n = newton_interp(table, x, i * 2 - 1), h = hermit_interp(table, x, i, table.get_m() - 2);
//            tb[j][0] = i * 2 - 1;
//            tb[j][1] = n;
//            tb[j][2] = h;
//            tb[j][3] = fabs(n - h);
//            tb[j][4] = fabs(n - h) / fabs(n);
//            j++;
//        }
        for (int i = 1; i < table.get_n() - 1; i++)
        {
            double n = newton_interp(table, x, i), h = hermit_interp(table, x, i, table.get_m() - 2);
            tb[j][0] = i;
            tb[j][1] = n;
            tb[j][2] = h;
            tb[j][3] = fabs(n - h);
            tb[j][4] = fabs(n - h) / fabs(n);
            j++;
        }
        cout << tb;
    }
    catch (Error &e)
    {
        e.print_message();
    }

}

int has_root(Matrix &mtr);

void root()
{
    try
    {
        Matrix mtr = table;
        for (int i = 0; i < mtr.get_n(); i++)
        {
            double tmp = mtr[i][0];
            mtr[i][0] = mtr[i][1];
            mtr[i][1] = tmp;
        }
        mtr.sort();
        if(!has_root(mtr))
            throw MathError("There are no root");
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
        tb[0][0] = "Degree";
        tb[0][1] = "Root";
        for (int i = 0; i < table.get_n() - 1; i++)
        {
            double res = newton_interp(table, 0, i);
            tb[i - 1][0] = i;
            tb[i - 1][1] = res;
        }
        cout << tb;
    }
    catch (Error &e)
    {
        e.print_message();
    }
}

int has_root(Matrix &mtr)
{
    for (int i = 0; i < mtr.get_n() - 1; i++)
        if(mtr[i][0] * mtr[i + 1][0] <= 0)
            return 1;
    return 0;
}