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
    string str = "/mnt/FILES/projects/плюсы на кладбище/Doomed/files/Pascal/main.pas", py_file, word, buffer;
    char separator;
    bool fl1 = false, fl_Var = false;
    const int size = 27;
    int place = 0, kol = 0;
    Data database[size] = {{"write",    "Write",    "print"},
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

    ifstream o_Pas(str);
    if (o_Pas.is_open()) {
        str = "/mnt/FILES/projects/плюсы на кладбище/Doomed/files/Python/main.py";
        ofstream w_Py(str);
        if (w_Py.is_open()) {
                cout << "++";
                while(!o_Pas.eof()){
                    o_Pas.get(separator);
                    if(separator == ' ' && kol <= 4) kol++;
                    if(separator == '\n'){
                        w_Py << "\n";
                        kol = 0;
                    }
                    if(kol > 4) w_Py << " ";
                }
            }
            w_Py.close();
            o_Pas.close();
    }
    return 0;
}
