#include "common.h"

void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pauseEnter()
{
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void header(const string &title)
{
    cout << "\n"
         << string(25, '=') << endl;
    cout << title;
    cout << "\n"
         << string(25, '=') << endl;
}

int inputInt(const string &label)
{
    int x;
    while (true)
    {
        cout << label;
        if (cin >> x)
        {
            clearInput();
            return x;
        }
        clearInput();
        cout << "Input tidak valid. Silakan coba lagi.\n";
    }
}

string inputLine(const string &label)
{
    string s;
    cout << label;
    getline(cin, s);
    return s;
}