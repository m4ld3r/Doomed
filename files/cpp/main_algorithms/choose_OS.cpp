#include <iostream>
using namespace std;

int main(){
    int choose_OS = 0;
    while(choose_OS > 3 || choose_OS < 1){
        switch(choose_OS){
            case 1:
                system("sudo apt update && sudo apt -y install zenity gcc");
                break;
            case 2:
                system("yes | sudo pacman -Sy zenity gcc");
                break;
            case 3:
                system("sudo dnf update && sudo dnf -y install zenity gcc");
                break;
            default:
                cout << "1) Производная от Debian(Ubuntu, Mint, ZorinOS) или он сам;\n2)Производная Arch(Manjaro) или он сам\n3)Fedora\nПожалуйста выберите тип вашей системы:  ";
                cin >> choose_OS;
                break;
        }
    }
    return 0;
}
