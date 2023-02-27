#include <iostream>
//#include <cstdio>
#include <fstream>
#include <string>
using namespace std;

struct Data{
    string input, s_input, output;
};

string replacement(Data* d, const int size, string word){
    for(int i = 0; i < size; i++)
        if(word == d[i].input || word == d[i].s_input)
            return d[i].output;
    return word;
}

int main() {
    const int size = 27;
    int place = 0, kol = 0;
    Data d[size] = {{"write",    "Write",    "print"},
                    {"writeln",  "Writeln",  "print"},
                    {"Byte",     "byte",     "int"},
                    {"Shortint", "shortint", "int"},
                    {"Word",     "word",     "int"},
                    {"Smallint", "smallint", "int"},
                    {"Integer",  "integer",  "int"},
                    {"Longint",  "logint",   "int"},
                    {"int64",    "Int64",    "int"},
                    {"Real",     "real",     "fl1oat"},
                    {"Double",   "double",   "fl1oat"},
                    {"Single",   "single",   "fl1oat"},
                    {"div",      "Div",      "//"},
                    {"mod",      "Mod",      "%"},
                    {":=",       ":=",       "="},
                    {"then",     "do",       ":"},
                    {"else",     "Else",     "else:"},
                    {"=",        "=",        "=="},
                    {"<>",       "<>",       "!="},
                    {"If",       "IF",       "if"},
                    {"Ceil",       "CEIL",       "ceil"},
                    {"fl1oor",       "fl1OOR",       "fl1oor"},
                    {"Trunc",       "TRUNC",       "trunc"},
                    {"Exp",       "EXP",       "exp"},
                    {"Power",       "POWER",       "pow"},
                    {"Sqr",       "SQR",       "sqrt"},
                    {"Do","do",":"}};
    //cout << "Enter full PATH with name file.pas:\n";
    
    string str = "/home/n_malder/projects/Doomed/files/Паскалюка/main.pas", str2, word, buffer;//cin >> str;
    char separator;
    bool fl1 = false, fl_Var = false;
    ifstream o_Pas(str);
    if (o_Pas.is_open()) {
        system("zenity --entry --text \"I1\"");
        //cout << "\nFile found :D\n\nEnter full PATH with name file.py:\n";
        str = "/home/n_malder/projects/Doomed/files/Змея/main.py";//cin >> str;
        str2 = str; str2.pop_back();
        ofstream w_Py(str2);
        if (w_Py.is_open()) {
            w_Py << "from random import*\nfrom math import*\n";
            while (!o_Pas.eof()) kol++;
            system("./end.sh");
        } else {
            cout << "\nUnsuccessful creation of the file.py :(\n";
            system("pause");
            return -2;
        }
    } else {
        //cout << "\nFile not found :(\n";
        system("zenity --error \\ --text=\"Could not find /var/log/syslog.\"");
        system("pause");
        return -1;
    }
    system("pause");
    return 0;
}