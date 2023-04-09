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

    ifstream o_Pas(str);
    if (o_Pas.is_open()) {
        cout << "+1\n";
        str = "/mnt/FILES/projects/плюсы на кладбище/Doomed/files/Python/main.py";//cin >> str;
        py_file = str; py_file.pop_back();
        ofstream w_Py(py_file);
        if (w_Py.is_open()) {
            cout << "+2\n";
            /* w_Py << "from random import*\nfrom math import*\n"; *///прописать только от того, если используется в паскале
            while (!o_Pas.eof()) {
//READY
                if(fl1){
                    w_Py << "print()";
                    fl1 = false;
                }
                place = o_Pas.tellg();
                o_Pas.get(separator);
//READY
                if(separator == '\n') continue;
//READY
                if(separator == '\t'){
                    while(separator == '\t'){
                            kol++;
                            o_Pas.get(separator);
                    }
                }
                o_Pas.seekg(place);
                o_Pas >> word;
//READY
                if (word == "Program" || word == "program") {
                    o_Pas >> word;
                    o_Pas.get(separator);
                    kol = 0;
                    continue;
                }
//READY (50/50) беz массивов
                if (word == "var" || word == "Var") {
                    while(word.back() != ';')
                        o_Pas >> word;
                    word.pop_back();
                    buffer = replacement(d, size, word);
                    kol = 0;
                    continue;
                }
//READY
                if(word=="Begin"||word=="End"||word=="end"||word=="begin" || word=="Begin;"||word=="End;"||word=="end;"||word=="begin;"){
                    o_Pas.get(separator);
                    kol = 0;
                    continue;
                }
                if(word=="End." || word=="end."){
                    o_Pas.get(separator);
                    kol = 0;
                    break;
                }
//READY
                if(word == "Read" || word == "read"){
                    o_Pas.get(separator);
                    o_Pas >> word;
                    while(!o_Pas.eof()){
                        for(int i = 0; i < kol-1; i++) w_Py << "\t";
                        if(word.back() == ';'){
                            if(word[0] == '(')word.erase(0, 1);
                            word.pop_back();word.pop_back();
                            w_Py << word << " = " << buffer << "(input())\n";
                            break;
                        }
                        else{
                            if(word[0] == '(')word.erase(0, 1);
                            word.pop_back();
                            w_Py << word << " = " << buffer << "(input())\n";
                        }
                        o_Pas >> word;
                    }
                    kol = 0;
                    continue;
                }
//READY
                if(word == "Readln" || word == "readln"){
                    o_Pas.get(separator);
                    o_Pas >> word;
                    while(!o_Pas.eof()){
                        for(int i = 0; i < kol-1; i++) w_Py << "\t";
                        if(word.back() == ';'){
                            if(word[0] == '(')word.erase(0, 1);
                            word.pop_back();word.pop_back();
                            w_Py << word << " = " << buffer << "(input())\n";
                            w_Py << "print()" << endl;
                            break;
                        }
                        else{
                            if(word[0] == '(')word.erase(0, 1);
                            word.pop_back();
                            w_Py << word << " = " << buffer << "(input())\n";
                        }
                        w_Py << "print()" << endl;
                        o_Pas >> word;
                    }
                    kol = 0;
                    continue;
                }
//READY
                if(word == "Random" || word == "random"){
                    w_Py << "random.randint";
                    kol = 0;
                    continue;
                }
//READY
                if(word == "for"){
                    o_Pas >> word;
                    w_Py << "for " << word << " in range (";
                    o_Pas >> word >> word;
                    w_Py << word;
                    o_Pas >> word >> word;
                    w_Py << " ," << word << ")";
                    continue;
                }
//READY
                else {
                    if(word == "Readln" || word == "readln") fl1 = true;
                    if (word.back() == ';') word.pop_back();
                    word = replacement(d, size, word);
                    for(int i = 0; i < kol-1; i++) w_Py << "\t";
                    w_Py << word;
                    o_Pas.get(separator);
                    w_Py << separator;
                    kol = 0;
                    continue;
                }
            }
            w_Py.close();
            o_Pas.close();
//READY
            ifstream pythonB(py_file); ofstream pythonA(str);
            if(pythonB.is_open() && pythonA.is_open()){
                while(!pythonB.eof()){
                    pythonB.get(separator);
                    if(separator == '\'' || separator == '‘' || separator == '’') 
                        pythonA << '"';
                    else pythonA << separator;
                }
                pythonA.close();
                pythonB.close();
                remove(py_file.c_str());
            }
        }
    }
    return 0;
}
