#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Data{
    string input, s_input, output;
};

string Replacement(Data* database, const int size, string word){
    for(int i = 0; i < size; i++)
        if(word == database[i].input || word == database[i].s_input)
            return database[i].output;
    return word;
}

int main() {
    string str = "/mnt/FILES/projects/плюсы на кладбище/Doomed/files/Pascal/main.pas", py_file, word, buffer;
    char separator;
    bool insert_before = true;
    const int size = 27;
    int place = 0, number_spaces = 0;
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
                while(!o_Pas.eof()){
                    place = o_Pas.tellg();
                    o_Pas.get(separator);
                    if(separator == '\n'){
                        number_spaces = 0;
                        insert_before = true;
                        w_Py << "\n";
                        continue;
                    }
                    if(separator == ' '){
                        if(number_spaces <= 4) number_spaces++;
                        else w_Py << " ";
                    } 
                    else{
                        o_Pas.seekg(place);
                        if(number_spaces > 4 && insert_before){
                            w_Py << " ";
                            insert_before = false;
                        }
                        o_Pas >> word;
                        buffer = Replacement(database, size, word);
                        if(buffer != word) w_Py << buffer;
                        /* else{ */
                            
                        /* } */
                    }
                }
            }
            w_Py.close();
            o_Pas.close();
    }
    return 0;
}
