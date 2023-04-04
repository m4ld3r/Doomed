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
    string str, py_file, word, buffer;
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

    system("FILE=\`zenity --file-selection --title=\"Select .pas file\"\` && echo \"$FILE\" > bufer");
    ifstream path_to_file("bufer");
    if(path_to_file.is_open()){
         getline(path_to_file, str);
         string check_pas = str.substr(str.size()-4);
         if(check_pas != ".pas") system("zenity --error \ --text=\"Invalid name of file\"");
         system ("rm bufer");
    }
    

    ifstream o_Pas(str);
    if (o_Pas.is_open()) {
        system("zenity --entry --text \"I1\"");
        //cout << "\nFile found :D\n\nEnter full PATH with name file.py:\n";
        str = "/home/n_malder/projects/Doomed/files/Змея/main.py";//cin >> str;
        py_file = str; py_file.pop_back();
        ofstream w_Py(py_file);
        if (w_Py.is_open()) {
            w_Py << "from random import*\nfrom math import*\n";
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
            system("(echo 10; sleep 1; echo 30; sleep 1; echo 40; sleep 1; echo 50; sleep 1; echo 60; sleep 1; echo 70; sleep 1; echo 80; sleep 1; echo 90; sleep 1; echo 100; sleep 1;) | zenity --progress \\ --title=\"Update System Logs\" \\ --text=\"Scanning mail logs...\" \\ --percentage=0");
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
