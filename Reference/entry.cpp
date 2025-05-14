// IMPORTS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cctype>
#include <algorithm>
#include <cctype>
#include <limits>
#include <regex>
#include <cmath>

// NAMESPACES
using namespace std;

/* ___________________________ VECTORS (MINI DATABASE) ___________________________ */

// ACCOUNTS
int account_count = 2;
vector<vector<string>> accounts = {
//        ID      AUTHORIZATON          USERNAMES             PASSWORDS
    {    "0",       "ADMIN",            "devacc",              "admin"        },
    {    "1",       "USER",             "KristoFrr",           "GodDid23"     },
    {    "2",       "USER",             "Chris2",              "Nwnw244"      },
};

// All products are added here
int product_count = 10;
vector<vector<string>> all_products = {
//       ID         PRODUCT                 MODEL                    PRICE             LOCATION              TYPE       WEIGHT
    {   "0",        "Guitar",           "Manila 2020",               "2500",         "Tanza Cavite",          "1",      "3.5"     },
    {   "1",        "Perfume",          "Eau de Mystique",           "500",          "Cavite City",           "2",      "0.2"     },
    {   "2",        "Fan",              "BreezeMaster 3000",         "1100",         "Olivares Tagaytay",     "0",      "2.0"     },
    {   "3",        "Headphone",        "AudioWave Pro",             "1320",         "Quezon City",           "4",      "0.3"     },
    {   "4",        "Hoody",            "CozyWear Max",              "830",          "Amadeo Cavite",         "6",      "0.5"     },
    {   "5",        "Top Box",          "Storage King",              "2400",         "Tanza Cavite",          "5",      "4.0"     },
    {   "6",        "String Bag",       "Traveler's Companion",      "650",          "Mall Of Asia",          "0",      "0.4"     },
    {   "7",        "Fast Charger",     "SpeedCharge Elite",         "500",          "Indang Cavite",         "7",      "0.2"     },
    {   "8",        "Gaming Chair",     "Gamer's Throne X",          "5300",         "Mendez Cavite",         "0",      "12.0"    },
    {   "9",        "Rubiks 3x3",       "PuzzleMaster Cube",         "980",          "Indang Cavite",         "8",      "0.1"     },
    {   "10",       "Fast Charger V2",  "SpeedCharge Pro V2",        "660",          "Indang Cavite",         "7",      "0.2"     },
    {   "11",       "Branded Watch",    "Rolling ex",                "260",          "Trece Martires",        "0",      "0.1"     },
    {   "12",       "Gaming Chair",     "Gamer's Throne Pro",        "6200",         "Mendez Cavite",         "0",      "12.0"    },
    {   "13",       "Rubiks 3x3",       "PuzzleMaster Elite",        "1200",         "Indang Cavite",         "8",      "0.1"     },
    {   "14",       "Fast Charger V2",  "SpeedCharge Ultra V2",      "820",          "Indang Cavite",         "7",      "0.2"     },
    {   "15",       "Branded Watch",    "Rolling ex Pro",            "390",          "Trece Martires",        "0",      "0.1"     },
    {   "16",       "Guitar",           "Manila 2020 Pro",           "3500",         "Tanza Cavite",          "1",      "3.5"     },
};


// all account will have a list of product they sell (product id)
int account_product_id = 2;
vector<vector<int>> account_Products = {
//      ID          PRODUCTS
    {   0,      0,  1,  5,  6    }, // KcSean
    {   1,      2,  4,  7        }, // KristoFrr
    {   2,      3,  8,  9,  10   }  // Christiany
};

// all account will have a list of product cart (product id)
int account_carts_id = 2;
vector<vector<int>> account_carts = {
//      ID          PRODUCTS
    {   0,      2,  8,  4,  10                  }, // devacc
    {   1,      10, 1,  0,  6,  9,  3,  5       }, // KristoFrr
    {   2,      7,  0,  1,  5,  6,  2,  4,  2   }  // Christiany
};

/* ______________________________ GLOBAL VARIABLES _______________________________ */

// Setting
vector<string> exit_points = { "q", "x", "quit", "exit", "back", "0"};
vector<string> login_points = {"login", "log", "start", "l"};
vector<string> register_points = {"register", "reg", "r"};
vector<string> setting_points = {"setting", "settings", "set", "s"};
vector<string> right_page_points = {">", "d", "6", "*", "-"};
vector<string> left_page_points = {"<", "a", "4", "/", "+"};
vector<string> right2_page_points = {">>", "dd", "66", "**", "--"};
vector<string> left2_page_points = {"<<", "aa", "44", "//", "++"};


/* __________________________________ MAIN APP ___________________________________ */

// FUNCTIONS DECLARATION
void set_terminal_size();
void run_main_prompt();
void start_user_login();
void register_account();
void ecommerce_page(const int &user_id);
void cart_page(const int &user_id);
void profile_page(const int &user_id);
void open_settings();

// UIX FUNCTION
void print(const string &text, const int rm_space = 0, const string color = "\e[0m");
void print_error(const string &text, const int rm_space = 0);
void print_line(const char symbol = '_', const string &color = "\e[1;30m");
void print_gradient(const string &text, const int &color_start, const int &color_end, bool background = false);
string centered_str(const string &text, const int rm_space = 0);
string print_line_str(const char symbol);
string convert_case(const string &subject, const string &option = "");

// PRODUCT
void display_products(int start_index);
bool left_page_key(const string &input);
bool right_page_key(const string &input);
bool productExist(const int &product_id);
vector<int> buy_product(const int &user_id, const int &product_id);
bool buy_process(const vector<string> &cmndSp, const int &user_id);
int find_cart(const int &user_id);

// DATABASE
int find_cart(const int &user_id);

// ASCII ART
void image_loader(const string &name, const string &model, const int &price, const string &img_id, const int &prod_id);

void print_noPhoto(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[0;33m");
void print_guitar(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[0;93m");
void print_perfume(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[0;96m");
void print_bag(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;35m");
void print_headphone(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;37m");
void print_topBox(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;37m");
void print_hoody(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;31m");
void print_FastCharger(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;37m");
void print_Rubiks(const string &name, const string &model, const int &price, const int &id, const int &spacing = 0, const string &color = "\e[1;32m");

// KEYBINDS
bool go_back(const string input);
bool login_key(const string &input);
bool register_key(const string &input);
bool setting_key(const string &input);

// AUTHENTICATION
string account_exist(const string &username);
bool account_authentication(const string &password, const string &id);
bool register_filter_username(const string &username);
bool register_filter_password(const string &password, const string &username);

// Split function definition 
vector<string> split(const string &s, char delimiter){ 
    vector<string> tokens; string token; 
    stringstream ss(s); 
    while (getline(ss, token, delimiter)) { 
        tokens.push_back(token); 
    } 
    return tokens;
}

// GLOBAL VARIABLE
int term_width = 80; 
int term_height = 20;

// APP SETTING
int main() {

    // function stream
    set_terminal_size();
    run_main_prompt();
    
    return 0;
}

void run_main_prompt(){
    system("cls");

    char symbol = ' ';
    string line_color = "\e[47m";
    string user_prompt;

    do{
        cout << "\n\n";
        print_gradient(print_line_str(symbol), 244, 255, true);
        cout << "\n\n\n\n";

        print("LOGIN", 24);
        print("REGISTER", 27);
        print("SETTINGS", 27);
        print("EXIT", 27);

        cout << "\n\n\n\n";
        print_gradient(print_line_str(symbol), 244, 255, true);
        cout << "\n\n\n\n";

        print("USER: ", 2);
        cout.flush();

        cin >> user_prompt;
        user_prompt = convert_case(user_prompt, "lower");

        if(login_key(user_prompt)){
            // ENTER LOGIN
            start_user_login();
            continue;
        }
        else if(register_key(user_prompt)){
            // ENTER REGISTER
            register_account();
            continue;
        }
        else if(setting_key(user_prompt)){
            // ENTER SETTINGS
            open_settings();
            continue;
        }
        else if(!go_back(user_prompt)){
            // INVALID
            cout<< "\n\n";
            print_error("Invalid Input");
            Sleep(1000);
            system("cls");
            cout.flush();
        }
        
    }
    while(!go_back(user_prompt));

    cout << "\n\n\n";
    print(". . . SHUTTING DOWN . . .", 0, "\e[1;93m");
    Sleep(3000);
    system("cls");
    exit(0);
}

// GO BACK ~ EXIT
bool go_back(const string input){
    for(string key : exit_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}

// LOGIN
bool login_key(const string &input){
    for(string key : login_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}

// REGISTER
bool register_key(const string &input){
    for(string key : register_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}

// SETTINGS
bool setting_key(const string &input){
    for(string key : setting_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}

bool right_page_key(const string &input){
    for(string key : right_page_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}
bool right2_page_key(const string &input){
    for(string key : right2_page_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}
bool left_page_key(const string &input){
    for(string key : left_page_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}
bool left2_page_key(const string &input){
    for(string key : left2_page_points){
        if(key == convert_case(input, "lower")){
            return true;
        }
    }
    return false;
}

/* ___________________________ SETTINGS PAGE FUNCTIONS ___________________________ */

// SETTINGS PAGE
void open_settings() {
    system("cls");
    cin.ignore();
    
    while(true) {
        cout << "\n";
        print_gradient(print_line_str('='), 35, 40);
        cout << "\n\n";
        
        print("SETTINGS", 0, "\e[1;36m");
        cout << "\n\n";
        
        // Display current keybinds
        print("Current Keybinds:", 0, "\e[0;33m");
        cout << "\n\n";
        
        string exit_str = "";
        for(string key : exit_points) exit_str += key + " ";
        print("Exit: ", 7, "\e[1;36m");cout <<  exit_str;
        cout << "\n";
        
        string login_str = "";
        for(string key : login_points) login_str += key + " ";
        print("Login: ", 7, "\e[1;36m"); cout << login_str;
        cout << "\n";
        
        string register_str = "";
        for(string key : register_points) register_str += key + " ";
        print("Register: ", 9, "\e[1;36m"); cout << register_str;
        cout << "\n";
        
        string settings_str = "";
        for(string key : setting_points) settings_str += key + " ";
        print("Settings: ", 9, "\e[1;36m"); cout << settings_str;
        cout << "\n";
        
        string right_str = "";
        for(string key : right_page_points) right_str += key + " ";
        print("Page Right: ", 10, "\e[1;36m"); cout << right_str;
        cout << "\n";
        
        string left_str = "";
        for(string key : left_page_points) left_str += key + " ";
        print("Page Left: ", 9, "\e[1;36m"); cout << left_str;
        cout << "\n\n";
        
        print_gradient(print_line_str('-'), 35, 40);
        cout << "\n\n";
        
        print("Commands:", 0, "\e[0;36m");
        cout << "\n";
        print("add [category] [key] - Add new keybind", 2);
        cout << "\n";
        print("remove [category] [key] - Remove keybind", 2);
        cout << "\n\n";
        
        print("Command: ", 2, "\e[0;33m");
        string command;
        getline(cin, command);
        
        // Process commands
        if(go_back(command)) {
            break;
        }
        
        vector<string> cmds = split(command, ' ');
        if(cmds.size() < 3) {
            print_error("Invalid command format");
            Sleep(1500);
            system("cls");
            continue;
        }
        
        string action = convert_case(cmds[0], "lower");
        string category = convert_case(cmds[1], "lower");
        string key = cmds[2];
        
        vector<string>* target = nullptr;
        
        // Determine target vector
        if(category == "exit") target = &exit_points;
        else if(category == "login") target = &login_points;
        else if(category == "register") target = &register_points;
        else if(category == "settings") target = &setting_points;
        else if(category == "right") {
            target = &right_page_points;
            // Update right2_page_points
            if(action == "add") {
                string doubled_key = key + key;
                right2_page_points.push_back(doubled_key);
            }
            else if(action == "remove") {
                string doubled_key = key + key;
                auto it = find(right2_page_points.begin(), right2_page_points.end(), doubled_key);
                if(it != right2_page_points.end()) {
                    right2_page_points.erase(it);
                }
            }
        }
        else if(category == "left") {
            target = &left_page_points;
            // Update left2_page_points
            if(action == "add") {
                string doubled_key = key + key;
                left2_page_points.push_back(doubled_key);
            }
            else if(action == "remove") {
                string doubled_key = key + key;
                auto it = find(left2_page_points.begin(), left2_page_points.end(), doubled_key);
                if(it != left2_page_points.end()) {
                    left2_page_points.erase(it);
                }
            }
        }
        else {
            print_error("Invalid category");
            Sleep(1500);
            system("cls");
            continue;
        }
        
        if(action == "add") {
            // Check if key already exists
            if(find(target->begin(), target->end(), key) != target->end()) {
                print_error("Key already exists in this category");
            } else {
                target->push_back(key);
                print("Key added successfully", 0, "\e[0;32m");
            }
        }
        else if(action == "remove") {
            // Check if key exists before removing
            auto it = find(target->begin(), target->end(), key);
            if(it != target->end()) {
                target->erase(it);
                print("Key removed successfully", 0, "\e[0;32m");
            } else {
                print_error("Key not found in this category");
            }
        }
        else {
            print_error("Invalid action");
        }
        
        Sleep(1500);
        system("cls");
    }
    
    system("cls");
}

/* ___________________________ USER INTERFACE FUNCTION ___________________________ */

// TERMINAL SIZE
void set_terminal_size(){

    ostringstream console;
    console << "mode con: cols=" << term_width << " lines=" <<term_height;
    string command = console.str();

    system(command.c_str());

    return;
}

// CENTER ALL TEXT
void print(const string &text, const int rm_space, const string color){ 
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) - rm_space; 
    cout << string(spaces, ' ') << color << fulltext << "\e[0m";
}

string centered_str(const string &text, const int rm_space){ 
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) - rm_space; 
    return string(spaces, ' ') + fulltext;
}

// ERROR PANEL
void print_error(const string &text, const int rm_space){
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) - rm_space; 
    cout << string(spaces, ' ') << "\x1B[31m" << fulltext << "\e[0m";
}

// ADD A LINE TO THE TERMINAL
void print_line(const char symbol, const string &color){
    cout << color << string(term_width, symbol) << "\n\e[0m" << endl;
}

// CREATE A LINE FOR MODIFICATION
string print_line_str(const char symbol){
    return string(term_width, symbol);
}

// CHANGE A STRING'S CASE
string convert_case(const string &subject, const string &option) {
    string result = subject;

    if (option == "lower") {
        transform(result.begin(), result.end(), result.begin(), ::tolower);
    } else if (option == "upper") {
        transform(result.begin(), result.end(), result.begin(), ::toupper);
    }else{
        bool capitalize = true;
        for (char &ch : result) {
            if (isspace(ch)) {
                capitalize = true;
            } else if (capitalize) {
                ch = toupper(ch);
                capitalize = false;
            } else {
                ch = tolower(ch);
            }
        }
    }

    return result;
}

void print_gradient(const string &text, const int &color_start, const int &color_end, bool background) {
    int color_range = color_end - color_start;
    int text_length = text.length();

    for (int i = 0; i < text_length; ++i) {
        int color_code = color_start + (color_range * i / text_length);
        if (background) {
            cout << "\033[48;5;" << color_code << "m\033[38;5;" << color_code << "m" << text[i];
        } else {
            cout << "\033[38;5;" << color_code << "m" << text[i];
        }
    }
    cout << "\033[0m"; // Reset color
}

/* ______________________________ ACCOUNT FUNCTIONS ______________________________ */

// checks if the user is registered in database
void start_user_login(){

    system("cls");
    // UI
    char symbol = '_';
    string login_color = "\e[1;32m";    // GREEN
    string prompt_color = "\e[0;36m";   // CYAN
    int prompt_space = 5;

    // DISPLAY PAGE
    cout << "\n";
    print_gradient(print_line_str(symbol), 119, 123);
    cout << "\n\n\n\n";

    // prompt
    print("L O G I N\n\n", 0, login_color);
    print("Username: \n", prompt_space, prompt_color);
    print("Password: \n", prompt_space, prompt_color);

    cout << "\n\n\n\n\n\n\n";
    print_gradient(print_line_str(symbol), 119, 123);
    cout << "\n\n";
    cout.flush();

    string ext_color = "\e[1;30m";
    cout << ext_color << "\nExit: \e" << "\e[0m";
    for(string key : exit_points){
        cout << ext_color << key <<  " \e[0m";
    }
    cout << "\r";

    // USER INPUT
    
    // move cursor up
    cout << "\033[12A";
    cout << "\033[" << term_width/2 << "C";

    // ask user for username
    string username;
    cin >> username;

    string account_id = account_exist(username); 

    if(go_back(username)){
        cout.flush();
        system("cls");
        return run_main_prompt();
    }

    // USERNAME EXIST
    if(account_id != "None"){
        while(true){
            // move cursor down
            cout << "\033[A";
            cout << "\033[" << term_width/2 -1 << "C";
            cout << "\033[B";
            cout << "\033[" << 0 << "C";

            // ask user password
            string password;
            cin >> password;
            cin.ignore();
            cout << "\n";

            if(go_back(password)){
                cout.flush();
                system("cls");
                return;
            }

            // CORRECT PASSWORD
            if(account_authentication(password, account_id)){
                
                string color = "\e[1;42;37m"; // Cyan

                cout << "\n";
                print("      Account Verified      ", 0, color);
                Sleep(1500);

                cout << "\n\n\n";
                print(". . . FETCHING ACCOUNT DETAILS . . .", 0, "\e[1;33m");
                Sleep(3000);
                system("cls");
                return ecommerce_page(stoi(account_id));
            }

            // INCORRECT PASSWORD
            else{
                string color = "\e[1;31m"; // Red
                cout << "\n\n";
                print("      Incorrect Password. Try Again.      \n\n", 0, color);
                cout.flush();
                Sleep(1500);
                return start_user_login();
            }
        }
    }

    // USERNAME DONT EXIST
    else{
        string color = "\e[1;31m"; // Red
        cout << "\n\n\n\n";
        print("      ACCOUNT DOES NOT EXIST      \n\n", 0, color);
        print("- - - Register First - - -\n", 0, color);

        Sleep(2000);
        cout.flush();
        system("cls");

        // Restart Username
        return start_user_login();
    } 
}

// Checks if account is registered
string account_exist(const string &username){
    for(vector<string> account: accounts){
        if(account[2] == username){
            return account[0];
        }
    }
    return "None";
}

bool account_authentication(const string &password, const string &id){
 
    if(accounts[stoi(id)][3] == password){
        return true;
    }
    return false;
}

// delete an account to the database
void terminate_account(){
    return;
}

// get all product of an account
vector<vector<string>> get_account_product(){
    return {{""}};
}



/* ______________________________ REGISTER ACCOUNT ______________________________ */

// add an account to the database
void register_account(){
    
    system("cls");
    // UI
    char symbol = '=';
    string login_color = "\e[1;32m";    // GREEN
    string prompt_color = "\e[0;36m";   // CYAN
    int prompt_space = 5;

    // DISPLAY PAGE
    cout << "\n";
    print_gradient(print_line_str(symbol), 35, 40);
    cout << "\n\n\n\n";

    // prompt
    print("R E G I S T E R\n\n", 0, login_color);
    print("Username: \n", prompt_space, prompt_color);
    print("Password: \n", prompt_space, prompt_color);

    cout << "\n\n\n\n\n\n\n";
    print_gradient(print_line_str(symbol), 35, 40);
    cout << "\n\n";
    cout.flush();

    string ext_color = "\e[1;30m";
    cout << ext_color << "\nExit: \e" << "\e[0m";
    for(string key : exit_points){
        cout << ext_color << key <<  " \e[0m";
    }
    cout << "\r";

    // USER INPUT
    
    // move cursor up
    cout << "\033[12A";
    cout << "\033[" << term_width/2 << "C";

    // ask user for username
    string username;
    cin >> username;

    if(go_back(username)){
        cout.flush();
        system("cls");
        return run_main_prompt();
    }

    // FILTERING USERNAME
    if(!register_filter_username(username)){
        Sleep(2000);
        system("cls");
        register_account();
    }

    while(true){
        // move cursor down
        cout << "\033[A";
        cout << "\033[" << term_width/2 -1 << "C";
        cout << "\033[B";
        cout << "\033[" << 0 << "C";

        // ask user password
        string password;
        cin >> password;
        cin.ignore();
        cout << "\n";

        if(go_back(password)){
            cout.flush();
            system("cls");
            return run_main_prompt();
        }

        // FILTERING PASSWORD
        if(!register_filter_password(password, username)){
            Sleep(2000);
            system("cls");
            register_account();
        }

        account_count += 1;
        account_product_id += 1;
        account_carts_id += 1;

        // REGISTER THE ACCOUNT
        accounts.push_back({to_string(account_count), "USER", username, password});
        account_Products.push_back({account_product_id});
        account_carts.push_back({account_carts_id});

        // CONFIRMATION
        string color = "\e[1;42;37m"; // Cyan

        cout << "\n";
        print("      Account registered      ", 0, color);
        Sleep(1500);

        cout << "\n\n\n";
        print(". . . LOGGING IN . . .", 0, "\e[1;33m");
        Sleep(3000);
        system("cls");

        // redirect
        return ecommerce_page(account_count);
    }
}

bool register_filter_username(const string &username){

    if(account_exist(username) != "None"){
        // Username Already Exist.
        cout << "\n\n\n";
        print_error("Username already exist");
        return false;
    }

    if(username.length() <= 5){
        // Username too short
        cout << "\n\n\n";
        print_error("Username too short");
        return false;

    }

    if(regex_search(username, regex("[^a-zA-Z0-9]"))) {
        // Username contains special characters
        cout << "\n\n\n";
        print_error("Username can't have special characters");
        return false;
    }
    
    if(isdigit(username[0])){
        // Cant have number as first character
        cout << "\n\n\n";
        print_error("Username should start with a letter");
        return false;
    }


    return true;
}

bool register_filter_password(const string &password, const string &username){

    if(regex_search(password, regex("[^a-zA-Z0-9]"))) {
        // Username contains special characters
        cout << "\n\n\n";
        print_error("Password can't have special characters");
        return false;
    }

    if(password.length() < 6){
        // Username too short
        cout << "\n\n\n";
        print_error("Password too short");
        return false;

    }

    if(convert_case(password, "lower") == convert_case(username, "lower")){
        // Username too short
        cout << "\n\n\n";
        print_error("Password can't be the same as the username");
        return false;

    }

    if (!regex_search(password, regex("[a-z]"))) {
        // Password does not contain a lowercase letter
        cout << "\n\n\n";
        print_error("Password must contain at least one lowercase letter");
        return false;
    }

    if (!regex_search(password, regex("[A-Z]"))) {
        // Password does not contain an uppercase letter
        cout << "\n\n\n";
        print_error("Password must contain at least one uppercase letter");
        return false;
    }

    if (!regex_search(password, regex("[0-9]"))) {
        // Password does not contain a number
        cout << "\n\n\n";
        print_error("Password must contain at least one number");
        return false;
    }

    return true;

}


/* ______________________________ PRODUCT FUNCTIONS ______________________________ */

// profile page
void profile_page(const int &user_id) {
    while(true) {
        system("cls");
        char symbol = '@';
        
        // Get user details
        vector<string> user = accounts[user_id];
        
        // Display user profile
        cout << "\n";
        print_gradient(print_line_str(symbol), 35, 40);
        cout << "\n\n";
        
        print("PROFILE", 0, "\e[1;36m");
        cout << "\n\n";
        print("Username: " + user[2], 0, "\e[0;33m");
        cout << "\n";
        print("Account Type: " + user[1], 0, "\e[0;32m");
        cout << "\n";
        print("Account ID: " + user[0], 0, "\e[0;36m");
        cout << "\n\n";
        
        // Display controls
        print_gradient(print_line_str('_'), 35, 40);
        cout << "\n\n";
        print("CONTROLS", 0, "\e[1;35m");
        cout << "\n\n";
        print("Sell", 0, "\e[0;37m");
        cout << "\n";
        print("Remove", 0, "\e[0;37m");
        cout << "\n";
        print("Products", 0, "\e[0;37m");
        cout << "\n";
        print("Statistics", 0, "\e[0;37m");
        cout << "\n\n";
        print_gradient(print_line_str(symbol), 35, 40);
        cout << "\n\n";
        
        // Get command
        print("Command: ", 2, "\e[0;33m");
        string command;
        getline(cin, command);
        
        if(go_back(command)) {
            break;
        }
        
        // Process commands
        if(convert_case(command, "lower") == "sell") {
            // Random mock data
            vector<string> categories = {"Electronics", "Clothing", "Accessories", "Home"};
            vector<string> locations = {"Manila", "Cebu", "Davao", "Cavite"};
            
            system("cls");
            cout << "\n\n";
            print_gradient(print_line_str('#'), 40, 45);

            cout << "\n\n";
            print("ADD PRODUCT", 0, "\e[1;36m");
            cout << "\n\n";
            
            print("Name: ", 7, "\e[1;33m");
            cout << "\n\n";
            
            print("Model: ", 7, "\e[1;33m");
            cout << "\n\n";
            
            print("Price: ", 7, "\e[1;33m");
            cout << "\n\n";

            print("Weight: ", 8, "\e[1;33m");
            cout << "\n\n";

            print("Image Type: ", 10, "\e[1;33m"); 
            cout << "\n\n";
            
            print_gradient(print_line_str('#'), 40, 45);

            cout << "\033[10A\033[43D";
            string name;
            getline(cin, name);

            cout << "\033[1B\033[36C";
            string model;
            getline(cin, model);

            cout << "\033[1B\033[36C";
            string price;
            getline(cin, price);

            cout << "\033[1B\033[36C";
            string weight;
            getline(cin, weight);

            cout << "\033[1B\033[36C";
            string type;
            getline(cin, type);

            // Add to products vector
            string new_id = to_string(all_products.size());
            all_products.push_back({new_id, name, model, price, locations[rand() % locations.size()], type, weight});
            account_Products[user_id].push_back(stoi(new_id));
            
            print(". . . Product added successfully . . .", 0, "\e[1;32m");
            Sleep(1500);
        }
        else if(convert_case(command, "lower") == "products") {
            system("cls");
            cout << "\n";
            print_gradient(print_line_str(' '), 31, 34, true); 
            cout << "\n\n";
            print("YOUR PRODUCTS", 0, "\e[1;36m");
            cout << "\n";
            
            print_gradient(print_line_str('_'), 30, 34); 
            cout << "\n\n";

            for(int prod_id : account_Products[user_id]) {
                vector<string> product = all_products[prod_id];
                print(product[1] + " - $" + product[3], 0, "\e[0;33m");
                cout << "\n\n";
            }
            
            print_gradient(print_line_str(' '), 31, 34, true); 
            cout << "\n\n";
            print("Press Enter to continue...", 0, "\e[0;37m");
            cin.ignore();
        }
        else if(convert_case(command, "lower") == "remove" || convert_case(command, "lower") == "rm"){
            system("cls");
            cout << "\n";
            print_gradient(print_line_str('='), 35, 40);
            cout << "\n\n";
            print("YOUR PRODUCTS", 0, "\e[1;36m");
            cout << "\n";
            print_gradient(print_line_str('-'), 35, 40);
            cout << "\n\n";

            // Display user's products
            for(int prod_id : account_Products[user_id]) {
            vector<string> product = all_products[prod_id];
            print(product[1] + " (ID: " + product[0] + ") - $" + product[3], 0, "\e[0;33m");
            cout << "\n";
            }

            cout << "\n";
            print("Enter product ID to remove (or 'cancel'): ", 0, "\e[0;36m");
            string remove_id;
            cin >> remove_id;

            if(convert_case(remove_id, "lower") == "cancel") {
            continue;
            }

            // Validate input is a number
            if(!all_of(remove_id.begin(), remove_id.end(), ::isdigit)) {
            print("Invalid ID format", 0, "\e[0;31m");
            Sleep(1500);
            continue;
            }

            int id_to_remove = stoi(remove_id);
            auto& user_products = account_Products[user_id];
            auto it = find(user_products.begin(), user_products.end(), id_to_remove);

            if(it != user_products.end()) {
            user_products.erase(it);
            cout << "\n";
            print("Product removed successfully", 0, "\e[0;32m");
            } else {
            print("\nProduct not found in your listings", 0, "\e[0;31m");
            }
            
            Sleep(1500);
        }
        else if(convert_case(command, "lower") == "statistics" || convert_case(command, "lower") == "stats") {
            system("cls");
            cout << "\n";
            print("STATISTICS", 0, "\e[1;36m");
            cout << "\n\n";
            
            // Mock statistics
            int total_sales = rand() % 10000 + 5000;
            int products_sold = rand() % 50 + 10;
            vector<string> recent_transactions = {
                "Guitar sold for $2500",
                "Headphones sold for $1320",
                "Watch sold for $390",
                "Perfume sold for $500"
            };
            
            print("Total Sales: $" + to_string(total_sales), 0, "\e[0;32m");
            cout << "\n";
            print("Products Sold: " + to_string(products_sold), 0, "\e[0;33m");
            cout << "\n\n";
            print("Recent Transactions:", 0, "\e[1;35m");
            cout << "\n\n";
 
            print_gradient(print_line_str('_'), 18, 22, true); 
            cout << "\n";
            for(int i = 0; i < recent_transactions.size(); i++) {
                cout << "\n";
                print(recent_transactions[i]); cout <<"\n";
            }
            cout << "\n";
            print_gradient(print_line_str('_'), 18, 22, true); 
            
            cout << "\n";
            print("Press Enter to continue...", 0, "\e[0;37m");
            cin.ignore();
        }
    }
    
    system("cls");
    return ecommerce_page(user_id);
}


// buy a product
vector<int> buy_product(const int &user_id, const int &product_id){
    // Check if product exists
    bool product_exists = false;
    for(vector<string> product : all_products){
        if(stoi(product[0]) == product_id){
            product_exists = true;
            break;
        }
    }
    if(!product_exists){
        print_error("Product does not exist");
        Sleep(1500);
        return {false};
    }

    // Check if user owns this product
    int list_speed = 700;
    vector<int> user_products = account_Products[find_cart(user_id)];
    for(int prod : user_products){
        if(prod == product_id){
            print_line('-', "\e[1;30m");
            print_error("Can't buy your own product\n\n", 0);
            print_line('-', "\e[1;30m");
            Sleep(list_speed);
            return {false};
        }
    }

    int total_Price;
    int shipping_fee;
    
    // If checks pass, proceed with purchase
    for(vector<string> product : all_products){
        if(stoi(product[0]) == product_id){
            float weight = stof(product[6]);
            int base_shipping = 50;
            
            // Calculate shipping fee based on weight
            if(weight <= 0.5) {
                shipping_fee = base_shipping;
            } else if(weight <= 2.0) {
                shipping_fee = base_shipping + (weight * 50);
            } else if(weight <= 5.0) {
                shipping_fee = base_shipping + (weight * 75); 
            } else {
                shipping_fee = base_shipping + (weight * 100);
            }

            total_Price = stoi(product[3]) + shipping_fee;
            string reset_c = "\e[0m";

            int p_len = product[1].size() + 15;
            int w_len = product[6].size()+ 17;
            int s_len = to_string(shipping_fee).size() + 19;

            // DISPLAY FORMAT
            print_gradient(print_line_str('_'), 35, 40);
            cout << "\e[0;33m" << "    Product: " << reset_c << product[1] << " ";
            print(" Weight: ", p_len, "\e[0;33m"); cout << product[6] + " kg";
            print("Product ID: ", w_len, "\e[1;36m"); cout << product[0];
            cout.flush();
            cout << "\n\r";
            cout << "\e[0;36m" << "    Shipping Fee: " << reset_c << "$" << to_string(shipping_fee) <<  " ";
            print("Total Price: ", s_len, "\e[1;32m"); cout << "$" << to_string(total_Price);
            cout << "\n";
            cout.flush();
            print_gradient(print_line_str('_'), 35, 40);
            Sleep(list_speed);

            break;
        }
    }
    return {true, product_id, total_Price, shipping_fee};
}

bool productExist(const int &product_id){
    for(vector<string> product : all_products){
        if(stoi(product[0]) == product_id){
            return true;
        }
    }
    return false;
}


/* ________________________________ CART FUNCTION ________________________________ */

class ResetException : public std::exception {
    private:
        int user_id;
    public:
        ResetException(int id) : user_id(id) {}
        int getUserId() const { return user_id; }
};

void cart_page(const int &user_id) {
    const int items_per_page = 5; 
    int current_page = 0;

    while (true) { 
        system("cls");
        
        // Color setting
        string reset_c = "\e[0m";
        string l_color = "\e[0;33m";
        string n_color = "\e[1;33m"; 
        string m_color = "\e[1;34m";
        string p_color = "\e[1;32m";
        string id_color = "\e[1;36m";

        const int items_per_page = 5; 
        int current_page = 0;

        while (true) { 
            system("cls");
            cout << " <<" << string(term_width * 0.40, ' ') <<" Your Cart " << string(term_width * 0.38, ' ') << " >>\n";


            // get the list of product from the account list
            vector<int> cart = account_carts[find_cart(user_id)];

            if(find_cart(user_id) == -1){
                print("cart_page(): Error, Account has no cart", 0, "\e[0;31m");
                Sleep(5000);
            }
            
            int start_index = current_page * items_per_page + 1; 
            int end_index = min(start_index + items_per_page, static_cast<int>(cart.size()));
            
            // retrieve from the all_product database
            for(int i = start_index; i < end_index; i++){
                for(vector<string> product : all_products){
                    if(stoi(product[0]) == cart[i] && i != 0){
                        print_gradient(print_line_str('_'), 35, 40);

                        // LENGTH OF STRINGS
                        int n_len = product[1].size() + 18;
                        int p_len = product[3].size() + 17;
                        int m_len = product[2].size() + 8;
                        
                        // DISPLAY FORMAT
                        cout << "\n";
                        cout << n_color << "    Name: " << reset_c << product[1] <<  " ";
                        print(" Model: ", n_len, m_color); cout << product[2];
                        print("Product ID: ", m_len, id_color); cout << product[0];
                        cout.flush();
                        cout << "\n\r";
                        cout << p_color << "    Price: "    << reset_c << product[3] <<  " ";
                        print(" Location: ", p_len, l_color); cout << product[4];
                        cout << "\n";
                        cout.flush();
                    }
                }
            }
            
            print_gradient(print_line_str('_'), 35, 40);
            
            // Pagination control 
            cout << "\n\n";
            cout << "    user: " << string(term_width * 0.48, ' ');
            print(" Buy     Clear", term_width/4, "\e[1;30m");
            cout << "\033[65D";
            string command; 
            cin >> command;
            
            int max_page = ceil(cart.size()/items_per_page);

    //      CLEAR COMMAND ____________________________________________________
            if(command == "clear") {
                account_carts[find_cart(user_id)].clear();
                print(". . . Removing All Products . . .", 0, "\e[0;32m");
                Sleep(2000);
                system("cls");
                cin.ignore();
                return ecommerce_page(user_id);
            }

    //      BUY COMMAND _____________________________________________________
            else if(convert_case(command, "lower") == "buy"){
                float total_weight = 0;
                int total_price = 0;
                int total_shipping = 0;
                vector<int> product_prices;
                vector<int> shipping_fees;
                vector<int> valid_products;
                system("cls");

                // Calculate totals for all items in cart 
                for(int i = 1; i < cart.size(); i++) {
                    vector<int> process = buy_product(user_id, cart[i]);
                    if(process[0]) { // Only process if buy_product returns true
                        // Get product details
                        for(vector<string> product : all_products) {
                            if(stoi(product[0]) == cart[i]) {
                                valid_products.push_back(cart[i]); // Track valid products
                                total_weight += stof(product[6]);
                                total_price += stoi(product[3]); 
                                shipping_fees.push_back(process[3]);
                                total_shipping += process[3];
                                break;
                            }
                        }
                    }
                }

                // Check if any valid products to purchase
                if(valid_products.empty()) {
                    print("\nNo valid products to purchase", 0, "\e[0;31m");
                    Sleep(2000);
                    return;
                }

                // Apply bulk shipping discount
                int items = valid_products.size();
                int discount = (items / 2) * 25; // 25% discount for every 2 items
                if(discount > 75) discount = 75;

                total_shipping = total_shipping * (100 - discount) / 100;
                int final_total = total_price + total_shipping;

                // Create lambda function for displaying summary
                auto printSummary = [&]() {
                    system("cls");
                    cout << "\n";
                    print_gradient(print_line_str('='), 35, 40);
                    cout << "\n\n";

                    print("PURCHASE SUMMARY", 0, "\e[1;36m"); 
                    cout << "\n\n";
                    print("Total Items: " + to_string(items), 0, "\e[0;33m");
                    cout << "\n";
                    print("Total Weight: " + to_string(total_weight) + " kg", 0, "\e[0;33m");
                    cout << "\n"; 
                    print("Products Total: $" + to_string(total_price), 0, "\e[0;32m");
                    cout << "\n";
                    print("Shipping Fee: $" + to_string(total_shipping), 0, "\e[0;36m");
                    cout << "\n";
                    print("FINAL TOTAL: $" + to_string(final_total), 0, "\e[1;32m");
                    cout << "\n\n";

                    print_gradient(print_line_str('='), 35, 40);
                    cout << "\n\n";
                };

                // Initial display
                printSummary();

                // Payment processing
                print("Payment: $", 2, "\e[0;33m");
                string payment_str;
                cin >> payment_str;

                cout << "\n";

                // Check for cancel
                if(convert_case(payment_str, "lower") == "cancel") {
                    cout << "\n\n";
                    print(" - - - Payment cancelled - - - ", 0, "\e[0;31m");
                    Sleep(1500);
                    system("cls");
                    cin.ignore();

                    // reset
                    return ecommerce_page(user_id);
                }

                int payment;
                while(true) {
                    // Check for cancel
                    if(convert_case(payment_str, "lower") == "cancel") {
                        cout << "\n\n";
                        print(" - - - Payment cancelled - - - ", 0, "\e[0;31m");
                        Sleep(1500);
                        system("cls");
                        cin.ignore();

                        // reset
                        return ecommerce_page(user_id);

                    }

                    // Validate payment input
                    bool valid_payment = true;
                    for(char c : payment_str) {
                        if(!isdigit(c)) {
                            valid_payment = false;
                            break;
                        }
                    }

                    if(!valid_payment) {
                        cout << "\n";
                        print("Invalid payment amount. Please try again.", 0, "\e[0;31m");
                        Sleep(1000);
                        printSummary();
                        print("Payment: $", 2, "\e[0;33m");
                        cin >> payment_str;
                        continue;
                    }

                    payment = stoi(payment_str);

                    if(payment < final_total) {
                        cout << "\n";
                        print("Insufficient payment amount. Please try again.", 0, "\e[0;31m");
                        Sleep(1000);
                        printSummary();
                        print("Payment: $", 2, "\e[0;33m");
                        cin >> payment_str;
                        continue;
                    }

                    // payment is valid
                    break;
                }

                int change = payment - final_total;
                print("Change: $" + to_string(change), 0, "\e[0;36m");
                cout << "\n\n";
                print(". . . Payment successful! . . .", 0, "\e[1;32m");
                cout << "\n";
                Sleep(2000);

                break;
            }

    //      RIGHT COMMAND ____________________________________________________
            else if (right_page_key(command)) {
                if (current_page + 1 <= max_page) {
                    current_page += 1;
                }
            } 
            else if (right2_page_key(command)) {
                if (current_page + 2 <= max_page) {
                    current_page += 2;
                }
                else if (current_page + 1 <= max_page) {
                    current_page += 1;
                }
            }
            else if(command == ">>>"){
                current_page = end_index - items_per_page;
            }

    //      LEFT COMMAND ____________________________________________________
            else if (left_page_key(command)) {
                if (current_page - 1 >= 0) {
                    current_page -= 1;
                }
            } 
            else if (left2_page_key(command)) {
                if (current_page - 2 >= 0) {
                    current_page -= 2;
                }
                else if (current_page - 1 >= 0) {
                    current_page -= 1;
                }
            }
            else if(command == "<<<"){
                current_page = 0;
            }

    //      GO BACK
            else if(go_back(command)){
                break;
            }
      
            else{ 
                cout << "\e[0;31m" << "\033[2K\rERROR: " << "\e[0m" << convert_case(command, "upper") << "\e[0;31m - Invalid Input\e[0m";
                cout.flush();
                Sleep(2000);
                continue;
            }
        }
        break;

    }
    // reset
    try {
        cin.ignore();
        throw ResetException(user_id); 
    }
    catch(const ResetException& e) {
        system("cls");
        ecommerce_page(e.getUserId());  // Restart ecommerce
    }
}

// Returns the index of the user cart (-1 if not found)
int find_cart(const int &user_id){

    for(int i = 0; i < account_carts.size(); i++){
        if(account_carts[i][0] == user_id){
            return i;
        }
    }
    return -1;
}


/* _______________________________ E-COMMERCE PAGE _______________________________ */
int loader_index = 0;

void ecommerce_page(const int &user_id){

    // Initial Load
    display_products(loader_index);

    string command;
    while (true) {
        getline(cin, command);
        vector<string> cmndSp = split(command, ' ');

//      GO COMMAND _____________________________________________________
        if(command == "go"){
            print_error("\033[A Incomplete \"Go\" command", 0);
            Sleep(2000);
        }
        else if(convert_case(cmndSp[0], "lower") == "go"){
            if(convert_case(cmndSp[1], "lower") == "cart"){
                // GO TO ACCOUNT CART
                cart_page(user_id);
                break;
            }
            else if(convert_case(cmndSp[1], "lower") == "profile"){
                // GO TO PROFILE
                profile_page(user_id);
                break;
            }
            else{
                print_error("\033[A Invalid Input", 0);
                cout.flush();
                Sleep(2000);
            }
        }
        

//      CART COMMAND _____________________________________________________
        else if (convert_case(cmndSp[0], "lower") == "cart"){
            
            // Make sure the command is complete
            if(cmndSp.size() < 2){
                print_error("\033[A Incomplete \"Cart\" command", 0);
                Sleep(2000);
                display_products(loader_index);
                continue;
            }

            // Filter invalid ID
            bool isDigit = true; 
            for (char c : cmndSp[1]) { 
                if (!isdigit(c)){ 
                    print_error("\033[A Invalid ID", 0);
                    isDigit = false;
                    Sleep(2000);
                    break;
                }
            }
            if(!isDigit){
                display_products(loader_index);
                continue;
            }

            // CHECK IF ID IS IN THE DATABASE
            if(stoi(cmndSp[1]) >= all_products.size()){
                print_error("\033[A Product ID: "+ cmndSp[1] +" doest not exist", 0);
                Sleep(2000);
                display_products(loader_index);
                continue;
            }
            print("\033[A ID: " + cmndSp[1] + " is added to the cart.", 0, "\e[0;32m");
            int cartID = stoi(cmndSp[1]);
            account_carts[find_cart(user_id)].push_back(cartID);

            Sleep(1500);
            system("cls");
        }

        //      BUY COMMAND _____________________________________________________
        else if(convert_case(cmndSp[0], "lower") == "buy"){
            if(!buy_process(cmndSp, user_id)){
                continue;
            }
        }



//      RIGHT COMMAND ____________________________________________________
        else if (right_page_key(command)) {
            if (loader_index + 2 < all_products.size()) {
                loader_index += 2;
            }
        } 
        else if (right2_page_key(command)) {
            if (loader_index + 4 < all_products.size()) {
                loader_index += 4;
            }
            else if (loader_index + 2 < all_products.size()) {
                loader_index += 2;
            }
        }
        else if(command == ">>>"){
            loader_index = all_products.size()-2;
        }


//      LEFT COMMAND ____________________________________________________
        else if (left_page_key(command)) {
            if (loader_index - 2 >= 0) {
                loader_index -= 2;
            }
        } 
        else if (left2_page_key(command)) {
            if (loader_index - 4 >= 0) {
                loader_index -= 4;
            }
            else if (loader_index - 2 >= 0) {
                loader_index -= 2;
            }
        }
        else if(command == "<<<"){
            loader_index = 0;
        }


//      HOME PAGE _______________________________________________________
        else if(go_back(command)){
            system("cls");
            break;
        }

//      INVALID _________________________________________________________
        else {
            // Handle invalid input
            print_error("\033[A Invalid Input", 0);
            Sleep(1500);
            system("cls");
            break;
        }
        
        display_products(loader_index);
    }
    return;
}

// PROCESS OF BUYING A PRODUCT
bool buy_process(const vector<string> &cmndSp, const int &user_id){
    if(cmndSp.size() < 2){
        print_error("\033[A Incomplete \"Buy\" command", 0);
        Sleep(2000);
        display_products(loader_index);
        return false;
    }

    float total_weight = 0;
    int total_price = 0;
    int total_shipping = 0;
    vector<int> product_ids;
    vector<int> shipping_fees;
    vector<int> valid_products;

    system("cls");

    // Process "buy all" command
    if(convert_case(cmndSp[1], "lower") == "all") {
        for(vector<string> product : all_products) {
            vector<int> process = buy_product(user_id, stoi(product[0]));
            if(process[0]) {
                valid_products.push_back(stoi(product[0]));
                total_weight += stof(product[6]);
                total_price += stoi(product[3]);
                shipping_fees.push_back(process[3]);
                total_shipping += process[3];
            }
        }
    }
    // Process individual product IDs
    else {
        for(int i = 1; i < cmndSp.size(); i++) {
            // Validate product ID
            bool isDigit = true;
            for(char c : cmndSp[i]) {
                if(!isdigit(c)) {
                    isDigit = false;
                    break;
                }
            }

            if(!isDigit || !productExist(stoi(cmndSp[i]))) {
                print_error("\033[A Invalid product ID: " + cmndSp[i], 0);
                Sleep(2000);
                continue;
            }

            vector<int> process = buy_product(user_id, stoi(cmndSp[i]));
            if(process[0]) {
                valid_products.push_back(stoi(cmndSp[i]));
                for(vector<string> product : all_products) {
                    if(stoi(product[0]) == stoi(cmndSp[i])) {
                        total_weight += stof(product[6]);
                        total_price += stoi(product[3]);
                        shipping_fees.push_back(process[3]);
                        total_shipping += process[3];
                        break;
                    }
                }
            }
        }
    }

    // Check if any valid products to purchase
    if(valid_products.empty()) {
        cout << "\n";
        print("No valid products to purchase", 0, "\e[0;31m");
        Sleep(2000);
        display_products(loader_index);
        return false;
    }

    // Apply bulk shipping discount
    int items = valid_products.size();
    int discount = (items / 2) * 25; // 25% discount for every 2 items
    if(discount > 75) discount = 75;

    total_shipping = total_shipping * (100 - discount) / 100;
    int final_total = total_price + total_shipping;

    // Display summary
    auto printSummary = [&]() {
        system("cls");
        cout << "\n";
        print_gradient(print_line_str('='), 35, 40);
        cout << "\n\n";

        print("PURCHASE SUMMARY", 0, "\e[1;36m");
        cout << "\n\n"; 
        print("Total Items: " + to_string(items), 0, "\e[0;33m");
        cout << "\n";
        print("Total Weight: " + to_string(total_weight) + " kg", 0, "\e[0;33m");
        cout << "\n";
        print("Products Total: $" + to_string(total_price), 0, "\e[0;32m");
        cout << "\n";
        print("Shipping Fee: $" + to_string(total_shipping), 0, "\e[0;36m"); 
        cout << "\n";
        print("FINAL TOTAL: $" + to_string(final_total), 0, "\e[1;32m");
        cout << "\n\n";

        print_gradient(print_line_str('='), 35, 40);
        cout << "\n\n";
    };

    printSummary();

    // Payment processing
    print("Payment: $", 2, "\e[0;33m");
    string payment_str;
    cin >> payment_str;

    cout << "\n";

    // Check for cancel
    if(convert_case(payment_str, "lower") == "cancel") {
        cout << "\n\n";
        print(" - - - Payment cancelled - - - ", 0, "\e[0;31m");
        Sleep(1500);
        system("cls");
        display_products(loader_index);
        cin.ignore();
        return false;
    }

    int payment;
    while(true) {
        // Check for cancel
        if(convert_case(payment_str, "lower") == "cancel") {
            cout << "\n\n";
            print(" - - - Payment cancelled - - - ", 0, "\e[0;31m");
            Sleep(1500);
            system("cls");
            display_products(loader_index);
            cin.ignore();
            return false;
        }

        // Validate payment input
        bool valid_payment = true;
        for(char c : payment_str) {
            if(!isdigit(c)) {
                valid_payment = false;
                break;
            }
        }

        if(!valid_payment) {
            cout << "\n";
            print("Invalid payment amount. Please try again.", 0, "\e[0;31m");
            Sleep(1000);
            printSummary();
            print("Payment: $", 2, "\e[0;33m");
            cin >> payment_str;
            continue;
        }

        payment = stoi(payment_str);

        if(payment < final_total) {
            cout << "\n";
            print("Insufficient payment amount. Please try again.", 0, "\e[0;31m");
            Sleep(1000);
            printSummary();
            print("Payment: $", 2, "\e[0;33m");
            cin >> payment_str;
            continue;
        }

        // If we get here, payment is valid
        break;
    }

    int change = payment - final_total;
    print("Change: $" + to_string(change), 0, "\e[0;36m");
    cout << "\n\n";
    print(". . . Payment successful! . . .", 0, "\e[1;32m");
    cout << "\n";
    cin.ignore();
    Sleep(2000);
    display_products(loader_index);
    return true;
}

// EASIER TO LOAD THE ASCII
void image_loader(const string &name, const string &model, const int &price, const string &img_id, const int &prod_id){

    // to autoamatically set the image by id integer
    switch(stoi(img_id)){
        case 0:
            return print_noPhoto(name, model, price, prod_id, 15);
        case 1:
            return print_guitar(name, model, price, prod_id, 15);
        case 2:
            return print_perfume(name, model, price, prod_id, 15);
        case 3:
            return print_bag(name, model, price, prod_id, 15);
        case 4:
            return print_headphone(name, model, price, prod_id, 15);
        case 5:
            return print_topBox(name, model, price, prod_id, 15);
        case 6:
            return print_hoody(name, model, price, prod_id, 15);
        case 7:
            return print_FastCharger(name, model, price, prod_id, 15);
        case 8:
            return print_Rubiks(name, model, price, prod_id, 15);

        default:
            return print_error("INVALID IMAGE ID: image_loader");
    }
}

// DISPLAY 2 PRODUCTS PER PAGE
void display_products(const int start_index) {
    system("cls");

    // NAV BAR INDICATOR
    cout << " <<" << string(term_width * 0.38, ' ') << " Command + ID " << string(term_width * 0.38, ' ') << ">>\n";
    
    // LINE
    print_gradient(print_line_str('_'), 184, 189);
    cout << "\n\n";

    // will load the product image by pair
    for (int i = start_index; i < start_index + 2 && i < all_products.size(); ++i) {
        // Loader
        image_loader(all_products[i][1], all_products[i][2], stoi(all_products[i][3]), all_products[i][5], stoi(all_products[i][0]));
        
        if (i < start_index + 1) {
            print_gradient(print_line_str('_'), 184, 189);
            cout << "\n\n";
        }
    }

    // LINE
    print_gradient(print_line_str('_'), 184, 189);
    cout << "\n";

    // CONTROL
    cout << " user: " << string(term_width * 0.52, ' ');
    print("Profile     Cart", term_width/4, "\e[1;30m");
    cout << "\033[69D";
}


/* ______________________________ PRODUCT ASCII ART ______________________________ */

void print_guitar(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color){
    print(      "&"         , spacing, color); cout << "\n";
    print(      "#"         , spacing, color); cout << "\t\t" << name << "\n";
    print(     "_#_"        , spacing, color); cout << "\t\t" << model << "\n";
    print(    "( # )"       , spacing, color); cout << "\n";
    print(    "/ 0 \\"      , spacing, color); cout << "\n";
    print(   "( === )"      , spacing, color); cout << "\t\t" << "$" << price << "\n";
    print(   "` --- ' "     , spacing, color); cout << "\t\t" << "ID: " << id << "\n";
}

void print_perfume(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print(     "[@_@]"      , spacing, color); cout << "\n";
    print(     " [_] "      , spacing, color); cout << "\t\t" << name << "\n";
    print(     "[ ` ]"      , spacing, color); cout << "\t\t" << model << "\n";
    print(    "/ ` ` \\"   , spacing, color); cout << "\n";
    print(   "[~` ~ `~]"    , spacing, color); cout << "\t\t" << "$" << price << "\n";
    print(   "[_______]"    , spacing, color); cout << "\t\t" << "ID: " << id << "\n";
}

void print_bag(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print(      "___"       , spacing, color); cout << "\n";
    print(     "/   \\"     , spacing, color); cout << "\t\t" << name << "\n";
    print(    "/     \\"    , spacing, color); cout << "\t\t" << model << "\n";
    print(    "|_____|"     , spacing, color); cout << "\n";
    print(   "/  `^`  \\"   , spacing, color); cout << "\n";
    print(   "[   0   ]"    , spacing, color); cout << "\t\t" << "$" << price << "\n";
    print(  "\\_______/"    , spacing, color); cout << "\t\t" << "ID: " << id << "\n";
}

void print_headphone(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print(    "_______"     , spacing, color); cout << "\n";
    print(   "/       \\"   , spacing, color); cout << "\t\t" << name << "\n";
    print(   "|       |"    , spacing, color); cout << "\t\t" << model << "\n";
    print(   "|       |"    , spacing, color); cout << "\n";
    print( "[00]     [00]"  , spacing, color); cout << "\t\t" << "$" << price << "\n";
    print( "[00]     [00]"  , spacing, color); cout << "\t\t" << "ID: " << id << "\n";
    print( "             "  , spacing, color); cout << "\n";
}

void print_topBox(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print( "_____________"  , spacing, color); cout << "\t\t" << name << "\n";
    print("/_____[o]_____\\", spacing, color); cout << "\t" << model << "\n";
    print("|     ^&^     |" , spacing, color); cout << "\n";
    print("|_____________|" , spacing, color); cout << "\t" << "$" << price << "\n";
    print("[_____________]" , spacing, color); cout << "\t" << "ID: " << id << "\n";
    print( "             "  , spacing, color); cout << "\n";

}

void print_hoody(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print(     ",o^o,"        , spacing, color); cout << "\n";
    print(  "  (     )  "     , spacing, color); cout << "\t\t" << name << "\n";
    print(  "__|_   _|__"     , spacing, color); cout << "\t\t" << model << "\n";
    print( "/           \\"  , spacing, color); cout << "\n";
    print( "| | HAPPY | |"   , spacing, color); cout << "\n";
    print( "| |  GUY  | |"   , spacing, color); cout << "\t\t" << "$" << price << "\n";
    print("\\,[__. __ ] /"  , spacing, color); cout << "\t\t" << "ID: " << id << "\n";
}

void print_FastCharger(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print( "__|_|__     ", spacing, color); cout << "\t\t" << name << "\n";
    print("|       |  X ", spacing, color); cout << "\t\t" << model << "\n";
    print("|       | [#]", spacing, color); cout << "\n";
    print("|_______|  | ", spacing, color); cout << "\n";
    print("|_______|  | ", spacing, color); cout << "\t\t" << "$" << price << "\n";
    print("   |_|     | ", spacing, color); cout << "\t\t" << "ID: " << id << "\n";
    print("    |______| ", spacing, color); cout << "\n";
}

void print_Rubiks(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color) {
    print("________________", spacing, color); cout << "\n";
    print("|    |    |    |", spacing, color); cout << "\t" << name << "\n";
    print("|____|____|____|", spacing, color); cout << "\t" << model << "\n";
    print("|    |    |    |", spacing, color); cout << "\n";
    print("|____|____|____|", spacing, color); cout << "\n";
    print("|    |    |    |", spacing, color); cout << "\t" << "$" << price << "\n";
    print("|____|____|____|", spacing, color); cout << "\t" << "ID: " << id << "\n";
}

void print_noPhoto(const string &name, const string &model, const int &price, const int &id, const int &spacing, const string &color){

    print("________________", spacing, color); cout << "\n";
    print("|              |", spacing, color); cout << "\t" << name << "\n";
    print("|   NO PHOTO   |", spacing, color); cout << "\t" << model << "\n";
    print("|    xxxxxx    |", spacing, color); cout << "\n";
    print("|   PROVIDED   |", spacing, color); cout << "\t" << "$" << price << "\n";
    print("|____ ____ ____|", spacing, color); cout << "\t" << "ID: " << id << "\n";

}