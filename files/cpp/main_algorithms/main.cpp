#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
struct Data {string request, responce;};
string Replacement(Data* database, const int size, string word) {
    for (int i = 0; i < size; i++)
        if (word == database[i].request)
            return database[i].responce;
    return word;
}

void End_processing(string py_file);/*в конце пройтись по питоновскому файлу для поправки недочётов обработки
3. Подумать насчёт констант что сделать (напоминаю что в дальнейшем они должны все быть в верхнем регистре)
*/

int main() {
    string str = "../../Pascal/main.pas", py_file, word, buffer;
    char separator;
    bool insert_before = true, insert_enter = false, insert_math_bibl = false;
    const int size = 16;
    int place = 0, number_spaces = 0;//не забыть про char
    Data database[size] = {{"write",   "print"},
                           {"integer", "int"},
                           {"real",    "float"},
                           {"char",    "string"},
                           {"string",  "string"},
                           {"boolean", "bool"},
                           {"div",     "//"},
                           {"mod",     "%"},
                           {":=",      "="},
                           {"then",    ":"},
                           {"do",      ":"},
                           {"else",    "else:"},
                           {"=",       "=="},
                           {"<>",      "!="},
                           {"If",      "if"},
                           {"trunc",   "trunc"}};

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
                    w_Py << word;
                }
            }
            w_Py.close();
            o_Pas.close();
            End_processing(str);
        }
    }
    return 0;
}
//пока новых задумок нет
void End_processing(string py_file) {
    string line;
    char separator;
    int place;

    system("touch buffer");
    ifstream file(py_file);
    ofstream buffer("buffer");
    while (getline(file, line)) buffer << line << endl;
    buffer.close();
    file.close();

    ifstream last_change("buffer");
    ofstream py(py_file);
    while (!last_change.eof()) {
        place = last_change.tellg();
        last_change.get(separator);
        if (separator == ' ') {
            getline(last_change, line);
            if (line != "") py << line << endl;
            else continue;
        } else {
            last_change.seekg(place);
            getline(last_change, line);
            if (line != "") py << line << endl;
            place = last_change.tellg();
            last_change.get(separator);
            if (separator == '\n') break;
            else last_change.seekg(place);
            if (line == "") continue;
        }
    }
    last_change.close();
    py.close();
    system("rm buffer");
}
