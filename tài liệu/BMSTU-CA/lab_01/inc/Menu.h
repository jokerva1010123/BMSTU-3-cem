#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

#include "MyErrors.h"

#define EXIT_CODE 0

using namespace std;

class MenuItem;

class Menu
{
private:
    vector<MenuItem> item_vec;
    bool is_main = false;

    void PrintList();

public:
    Menu();

    Menu(bool is_main);

    void AddItem(const MenuItem &item);

    void AddItem(int i, const MenuItem &item);

    void DelItem(int i);

    MenuItem &GetItem(int i);

    void show();
};

class MenuItem
{
private:
    typedef void (*funk_type)();

    string str;
    funk_type funk;
public:
    MenuItem(const char *str, funk_type funk);

    void Print(int i);

    void work();
};

template<class T>
void prompt_input(const char *str, T &val, const char *err_message = "")
{
    cout << str;
    //todo бработка некорректного ввода
    cin >> val;
}

template<class T>
void prompt_print(const char *str, T &val)
{
    cout << str << val << endl;
}

#endif
