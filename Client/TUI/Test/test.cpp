// main.cpp
#include <iostream>
#include <string>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define byte win_byte_override
#include <windows.h>
#undef byte

#include "uix.h"
#include "Color.h"
#include "Keybinds.h"

#include <sstream>
#include <cctype>
#include <algorithm>
#include <cctype>
#include <limits>
#include <regex>
#include <cmath>

using namespace Color;

int main() {
    set_terminal_size();
}

// LOGIN / REGISTER
void auth_page(string user_prompt){

    system("cls");

    string line_color = "\e[47m";
    

    do{
        space(2);
        print_gradient(line_str(' '), 227, 231, true);
        print_gradient(line_str(' '), 227, 231, true);
        space(4);

        print("LOGIN", -24);
        print("REGISTER", -27);
        print("SETTINGS", -27);
        print("EXIT", -27);

        space(4);
        print_gradient(line_str(' '), 227, 231, true);
        print_gradient(line_str(' '), 227, 231, true);
        space(4);

        print("USER: ", -2);
        cout.flush();

        cin >> user_prompt;
        user_prompt = convert_case(user_prompt, "lower");

        if(login_key(user_prompt)){
            // ENTER LOGIN
            // start_user_login();
            system("cls");
            cout.flush();
            continue;
        }
        else if(register_key(user_prompt)){
            // ENTER REGISTER
            // register_account();
            system("cls");
            cout.flush();
            continue;
        }
        else if(setting_key(user_prompt)){
            // ENTER SETTINGS
            // open_settings();
            system("cls");
            cout.flush();
            continue;
        }
        else if(exit_key(user_prompt)){
            space(3);
            print(". . . SHUTTING DOWN . . .", 0, "\e[1;93m");
            Sleep(3000);
            system("cls");
            exit(0);         
        }
        else{
            // INVALID
            space(2);
            print_error("Invalid Input");
            Sleep(1000);
            system("cls");
            cout.flush();

            continue;
        }
        
    }
    while(!exit_key(user_prompt));

}
