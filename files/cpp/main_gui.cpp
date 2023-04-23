#include <iostream>
#include <thread>
#include <fstream>
#include <string>
#include <thread>
using namespace std;

struct Data{
    string input, short_input, output;
};

string replacement(Data* database, const int size, string word){
    for(int i = 0; i < size; i++)
        if(word == d[i].input || word == d[i].s_input)
            return d[i].output;
    return word;
}

void Gui_Progress(){
    system("(echo \"20\" ; sleep 1 ; echo \"# Сканирование .pas файла\" ; sleep 1 ; echo \"40\" ; sleep 1 ; echo \"# Считывание кодировки\" ; sleep 1 ; echo \"60\" ; sleep 1 ; echo \"# Подсчёт кол-ва пробелов\" ; sleep 1 ; echo \"80\" ; sleep 1 ; echo \"# Трансляция в .py файл\" ; sleep 1 ; echo \"100\" ; sleep 1) | zenity --progress \ --title=\"Обработка\" \ --text=\"Сканирование .pas файла\" \ --percentage=0");
}

int main() {
    const int size = 27;
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
    string pas_file, py_file, word, buffer;
    char separator;
    bool fl1 = false, fl2 = false;
    int place = 0, kol = 0;
    system("zenity --warning \ --text=\"Для дальнейшей работы создайте файл с расширением .py\"");
    system("FILE=\`zenity --file-selection --title=\"Выберите файл с расширением .PAS\"\` && echo \"$FILE\" > bufer");
    ifstream buffer_file("bufer");
    if(buffer_file.is_open()){
        getline(buffer_file, pas_file);
        buffer_file.close();
        system("rm bufer");
        string check_pas = pas_file.substr(pas_file.size()-4);
        if(check_pas != ".pas"){
            system("zenity --error \ --text=\"Неправильное расширение файла для Pascal\"");
            return -32;
        }else{
            ifstream o_Pas(pas_file);
            if (o_Pas.is_open()) {
                system("FILE=\`zenity --file-selection --title=\"Выберите файл с расширением .PY\"\` && echo \"$FILE\" > bufer");        
                ifstream buffer_file("bufer");
                if(buffer_file.is_open()){
                    getline(buffer_file, py_file);
                    buffer_file.close();
                    system("rm bufer");
                    string check_py = py_file.substr(py_file.size()-3);
                    if(check_py != ".py"){
                        system("zenity --error \ --text=\"Неправильное расширение файла для Python\"");
                        return -31;
                    } else{
                        ofstream w_Py(py_file);
                        if (w_Py.is_open()) {
                            thread gui(Gui_Progress);
                            while(!w_Py.eof()){
                                
                            } 
                            gui.join();
                            system("zenity --info \ --text=\"Работа завершена\"");
                            o_Pas.close();
                            w_Py.close();

                        } else {
                            system("zenity --error \ --text=\"Ошибка открытия файла с расширением .py\"");
                            return -22;
                        }
                    }
                }else{
                    system("zenity --error \ --text=\"Ошибка обработки\"");
                    return -12;
                }
            } else {
                system("zenity --error \ --text=\"Ошибка открытия файла с расширением .pas\"");
                return -21;
            }
        }
    }else {
        system("zenity --error \ --text=\"Ошибка обработки\"");
        return -11;
    }

    return 0;
}
