#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

struct Data {
    string input, s_input, output;
};

string Replacement(Data* database, const int size, string word) {
    for (int i = 0; i < size; i++)
        if (word == database[i].input || word == database[i].s_input)
            return database[i].output;
    return word;
}

void End_processing();/*в конце пройтись по питоновскому файлу для поправки недочётов обработки
1. Проверка пустых строк;
2. Проверка пробелов перед словами в начале строки
3. Подумать насчёт констант что сделать (напоминаю что в дальнейшем они должны все быть в верхнем регистре)
*/

int main() {
    string str = "../../Pascal/main.pas", py_file, word, buffer;
    char separator;
    bool insert_before = true, insert_enter = false;
    const int size = 27;
    int place = 0, number_spaces = 0;
    Data database[size] = { {"write",    "Write",    "print"},
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
                    {"Do","do",":"} };

    ifstream o_Pas(str);
    if (o_Pas.is_open()) {
        str = "../../Python/main.py";
        ofstream w_Py(str);
        if (w_Py.is_open()) {
            while (!o_Pas.eof()) {
                place = o_Pas.tellg();
                o_Pas.get(separator);
//READY
                if (separator == '\n') {
                    number_spaces = 0;
                    insert_before = true;
                    w_Py << "\n";
                    continue;
                }
//READY
                if (separator == ' ') {
                    if (number_spaces <= 4) number_spaces++;
                    else w_Py << " ";
                }
//READY
                else {
                    o_Pas.seekg(place);
                    if (number_spaces > 4 && insert_before) {
                        w_Py << " ";
                        insert_before = false;
                    }
                    o_Pas >> word;
                    cout << word << endl;
                    if (word == "Begin" || word == "begin" || word == "End." || word == "end.") continue;
                    if (word == "Program" || word == "program") {
                        while (separator != '\n') o_Pas.get(separator);
                        continue;
                    }
                    if(word.back() == ';') word.pop_back();
                    buffer = Replacement(database, size, word);
                    if (buffer != word) {
                        o_Pas.get(separator);
                        w_Py << buffer << separator;
                        continue;
                    }
//ДОДЕЛАТЬ!!!
                    if (word == "Var" || word == "var") {
                        /*Есть задумка, чтоб считывать с пас файла имя переменных в массив, и потом в питоновском поправлять на нужный тип данных*/
                        while (separator != '\n') o_Pas.get(separator);
                        continue;
                    }
//READY
                    if (word == "const") {
                        while (separator != '\n') {
                            o_Pas >> word;
                            if (word.back() == ';') {
                                word.pop_back();
                                insert_enter = true;
                            }
                            transform(word.begin(), word.end(), word.begin(), [](char const& c) {return toupper(c); });
                            o_Pas.get(separator);
                            w_Py << word;
                            if (insert_enter) {
                                w_Py << '\n';
                                insert_enter = false;
                            }
                            if (separator != '\n') w_Py << separator;
                        }
                        continue;
                    }
//READY
                    if (word == "Read" || word == "read" || word == "Readln" || word == "readln") {
                        o_Pas >> word;
                        while (word.back() != ';') {
                            if (word.back() == ',') word.pop_back();
                            if (word != ")" && word != "(") w_Py << word << "=input();\n";
                            o_Pas >> word;
                        }
                        continue;
                    }
//READY
                    if(word == "sqr"){
                        o_Pas >> word >> word;
                        w_Py << word << "*" << word;
                        o_Pas >> word;
                        continue;
                    }
//READY
                    if(word == "random"){
                        cout << "+++\n";
                        w_Py << "randint(0, ";
                        while(word.back()!=')'){
                            o_Pas >> word;
                            if(word.back()!='(')w_Py << word;
                        }
                        continue;
                    }
//READY
                    if(word == "for"){
                        w_Py << word << " ";
                        o_Pas >> word;
                        w_Py << word << " in range(";
                        o_Pas >> word >> word;
                        w_Py << word << ", ";
                        o_Pas >> word >> word;
                        w_Py << word << ")";
                        continue;
                    }
                    if(word == "while"){

                    }
                    else w_Py << word;
                }
            }
        }
        w_Py.close();
        o_Pas.close();
    }
    return 0;
}
