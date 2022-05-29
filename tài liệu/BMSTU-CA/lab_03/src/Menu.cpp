#include "../inc/Menu.h"

Menu::Menu() : is_main(false)
{};

Menu::Menu(bool is_main) : is_main(is_main)
{};

void Menu::AddItem(const MenuItem &item)
{
    item_vec.push_back(item);
}

void Menu::AddItem(int i, const MenuItem &item)
{
    if (i < 1 || i > item_vec.size()) throw AccessError("Going beyond the menu list");
    auto it = item_vec.begin();
    for (int j = 0; j < i; j++) it++;
    item_vec.insert(it, item);
}


void Menu::DelItem(int i)
{
    if (i < 0 || i > item_vec.size() - 1) throw AccessError("Going beyond the menu list");
    auto it = item_vec.begin();
    for (int j = 0; j < i; j++) it++;
    item_vec.erase(it);
}

MenuItem &Menu::GetItem(int i)
{
    if (i < 0 || i > item_vec.size() - 1) throw AccessError("Going beyond the menu list");
    auto it = item_vec.begin();
    for (int j = 0; j < i; j++) it++;
    return *it;
}

void Menu::PrintList()
{
    int i = 1;
    for (auto item: item_vec)
        item.Print(i++);
    if (is_main)
        cout << "0) Exit" << endl;
    else
        cout << "0) Back" << endl;
    cout << "Choice: ";
}

void Menu::show()
{
    while (true)
    {
        int c;
        this->PrintList();
        cin >> c;
        if (c == EXIT_CODE)
            break;
        try
        {
            MenuItem &item = this->GetItem(c - 1);
            item.work();
        }
        catch (Error &e)
        {
            e.print_message();
        }
    }
}


MenuItem::MenuItem(const char *str, MenuItem::funk_type funk)
        : funk(funk)
{
    this->str = str;
}

void MenuItem::Print(int i)
{
    cout << i << ") " << str << endl;
}

void MenuItem::work()
{
    funk();
};


