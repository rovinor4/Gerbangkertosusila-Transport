#include "common.h"


static void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void pauseEnter() {
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void header(const string& title) {
    cout << "\n" << string(25,'=') << endl;
    cout << title << "\n";
    cout << "\n" << string(25,'=') << endl;
}

static int inputInt(const string& label) {
    int x;
    while (true) {
        cout << label;
        if (cin >> x) {
            clearInput();
            return x;
        }
        clearInput();
        cout << "Invalid input. Try again.\n";
    }
}

static string inputLine(const string& label) {
    string s;
    cout << label;
    getline(cin, s);
    return s;
}