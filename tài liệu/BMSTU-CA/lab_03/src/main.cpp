#include <iostream>

#include "Menu.h"
#include "interpolate.h"
#include "CppConsoleTable.hpp"
#include "Matrix.h"

using ConsoleTable = samilton::ConsoleTable;
using namespace std;

void noone();

void left();

void right();

void both();

void interp(Matrix &table, bool left, bool right);

void newton_table();

void newton_param();

Matrix table;


int main()
{
//    table.InputMatrix("data.txt");
//    double res = interpolate3x(table, 1.01, 1.01, 0, 3, 3, 3);
//    cout << res;
    try
    {
        table.InputMatrix("data.txt");
        Menu menu(true);
        menu.AddItem(MenuItem("All second derivative is 0", &noone));
        menu.AddItem(MenuItem("The second derivative on the left is equal to the derivative of the Newton polynomial",
                              &left));
        menu.AddItem(MenuItem("The second derivative on the right is equal to the derivative of the Newton polynomial",
                              &right));
        menu.AddItem(MenuItem("Both derivatives are equal to the derivative of the Newton polynomial", &both));
        menu.show();
    }
    catch (Error &e)
    {
        e.print_message();
    }

    return 0;
}

void noone()
{
    interp(table, false, false);
}

void left()
{
    interp(table, true, false);
}

void right()
{
    interp(table, false, true);
}

void both()
{
    interp(table, true, true);
}

void interp(Matrix &table, bool left, bool right)
{
    double x;
    prompt_input("Input x:", x);
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
    tb[0][0] = "x \\ Method";
    tb[0][1] = "Splines";
    tb[0][2] = "Newton";
    tb[0][3] = "Difference";

    double spline_res = spline_interp(table, x, left, right),
            newton_res = newton_interp(table, x, table.get_n() - 1);

    tb[1][0] = x;
    tb[1][1] = spline_res;
    tb[1][2] = newton_res;
    tb[1][3] = fabs(spline_res - newton_res);

    cout << tb;
}