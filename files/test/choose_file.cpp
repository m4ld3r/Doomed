#include <iostream>
#include <sstream>

int main()
{
    //zenity --file-selection --title="Selecciona un archivo"
    char char_array[] = {'S','T','E','C','H','I','E','S'};
    std::string str;
    std::stringstream strStream;
    strStream << char_array;
    strStream >> str;
    std::cout << str;

    return 0;
}
