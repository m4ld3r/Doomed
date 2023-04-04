#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){

    system("FILE=\`zenity --file-selection --title=\"Select .pas file\"\` && echo \"$FILE\" > bufer");
    ifstream path_to_file("bufer");
    string s;
    if(path_to_file.is_open()){
        getline(path_to_file, s);
        string check_pas = s.substr(s.size()-4);
        if(check_pas != ".pas") system("zenity --error \ --text=\"Invalid name of file\"");
        system ("rm bufer");
    }
    else system("zenity --error \ --text=\"Could not find files.pas\"");
    return 0;
}
