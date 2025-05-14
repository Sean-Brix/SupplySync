// main.cpp
#include <iostream>
#include <string>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define byte win_byte_override
#include <windows.h>
#undef byte

#include <sstream>
#include <cctype>
#include <algorithm>
#include <limits>
#include <regex>
#include <cmath>
#include <fstream>
#include <cstdio>  
#include <ctime>
#include <iomanip>
#include <vector>

// Headers
#include "uix.h"
#include "Color.h"
#include "Config.h"
#include "Keybinds.h"
#include "admin_dashboard.h"
#include "user_dashboard.h"

using namespace Color;
using namespace Config;
using namespace std;
const int MAX_ITEMS = 100;
struct Item {
    int id;
    string name;
    int quantity;
}; 

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
struct User {
    int id;
    string username;
    string password;
    string name;
    string dept;
    string userAccess;
}; 

struct RequestItem {
	int reqId;
    int itemId;
    string itemName;
    int itemQuan;
    string borrowerName;
    int borrowerId;
    string date;
}; 

struct BorrowedItem {
	int reqId;
    int itemId;
    string itemName;
    int itemQuan;
    string borrowerName;
    int borrowerId;
    string borrowDate;
    
};
struct ReturnedItem{
        	int itemId;
        	string itemName;
        	int itemQuan;
        	int borrowerId;
        	string borrowerName;
        	string borrowDate;
        	string dateReturn;
}; 






void adminDashboard(int id, string name ,string username, string department, string userAccess,string password);
void userDashboard(int id, string name ,string username, string department, string userAccess,string password);
void loginUser();
void open_settings();

void addUser(const User& user);
void addItem(const Item&item);

void readUsers(const bool isDelete = false);
void readItems(const bool isDelete = false);

void readAllUserRequest();
void readMyRequest(int id);
void readMyCancelled(int id);

void readMyBorrow(int id);
void readAllBorrowedItem();

void deleteItem(int idToDelete);
void deleteUser(int idToDelete);
void changePass(int id, string confirmedPass);

void approveRequest(int requestIdToApprove);
void cancelItems(int idToCancel);

void debug(const string bug, const int time = 3000);

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void debug(const string bug, const int time){
    clearScreen();
    space(5);
    print(("       " + bug + "       "), 0, {Color::bg_bright_green, Color::black});
    Sleep(time);
}

std::string getCurrentDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    std::ostringstream oss;
    oss << (1900 + localTime->tm_year) << "-"
        << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-"
        << std::setw(2) << std::setfill('0') << localTime->tm_mday;

    return oss.str();
}
//User ID getter
int getLastUserId() {
    ifstream file("data.txt");
    string line;
    int lastId = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        int id;
        if (iss >> id) {
            lastId = id;
        }
    }

    return lastId;
}


//Utem ID Getter
int getLastItemId() {
    ifstream file("item.txt");
    string line;
    int lastId = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        int id;
        if (iss >> id) {
            lastId = id;
        }
    }

    return lastId;
}
//Request Id getter
int getLastReqId() {
    ifstream file("requestItem.txt");
    string line;
    int lastId = 0;

    while (getline(file, line)) {
        istringstream iss(line);
        int id;
        if (iss >> id) {
            lastId = id;
        }
    }

    return lastId;
}

//Authentication// user dashboard
void loginUser() {
	clearScreen();

    system("cls");

    // UI
    char symbol = '_';

    // DISPLAY PAGE
    space();
    print_gradient(line_str(symbol), 89, 93);
    space(4);
    
    // prompt
    print("S I G N  I N", 0);
    space(3);
    print_input_box(20, 0, Config::color_theme, "username", false, "left");
    space(2);
    print_input_box(20, 0, Config::color_theme, "password", false, "left");

    space(3);
    print_gradient(line_str(symbol), 89, 93);
    space(2);
    cout.flush();

    string ext_color = Color::gray;
    cout << ext_color << "\nExit: \e" << "\e[0m";
    for(string key : exit_keybinds()){
        cout << ext_color << key <<  " \e[0m";
    }
    cout << "\r";

    // USER INPUT
    set_cursor(31, 8);
    
    // ask user for username
    string username;
    cin >> username;

    set_cursor(31, 12);

    if(back_key(username) || exit_key(username)){
        return;
    }

    string password;
    cin >> password;
	cin.ignore();

    if(back_key(password) || exit_key(password)){
        return;
    }

    ifstream file("./data.txt");
    if (!file.is_open()) {
        cout << "Unable to open user database.\n";
        return;
    }

    User user;
    bool loginSuccess = false;

    while (file >> user.id >> user.name >> user.username >> user.password >> user.dept >> user.userAccess) {
        if (user.username == username && user.password == password) {
            loginSuccess = true;
            break;
        }
    }

    file.close();

    if (loginSuccess) {
    	if(convert_case(user.userAccess, "lower") == "admin"){
            space(2);
            print("      Account Verified      ", 0, { Color::bg_light_green, Color::black});
            Sleep(3000);
            system("cls");
    		adminDashboard(user.id, user.name ,user.username ,user.dept , user.userAccess, user.password);
		}
        else if(convert_case(user.userAccess, "lower") == "user"){
            space(2);
            print("      Account Verified      ", 0, { Color::bg_light_green, Color::black });
            Sleep(3000);
            system("cls");
			userDashboard(user.id ,user.name ,user.username ,user.dept , user.userAccess,user.password);
		}
        else{
            print("     User dont have access     ", 0, { Color::bg_red, Color::white });
			return;
		}
		
    } 
    else {
        space(2);
        print("     Login Unsuccessful     ", 0, { Color::bg_red, Color::white });
        Sleep(2000);
        loginUser();
        return;
    }
}

//User adder
void addUser(const User& user) {
    ofstream file("data.txt", ios::app);
    if (file.is_open()) {
        file << user.id << " " << user.name << " " << user.username << " " << user.password << " " << user.dept << " "
		<<user.userAccess<< endl;

        file.close();
    }
}
//Item ADder
void addItem(const Item& item) {
    ofstream file("item.txt", ios::app);
    if (file.is_open()) {
        file << item.id << " " << item.name << " "<< item.quantity << endl;

        file.close();
        // cout << "Item added.\n";
    }
}

//user requesting an item to borrow
void requestItems(int idToBorrow,int quantity,string name, int id , string date) {
    int lastId = getLastReqId() +1;
    ifstream inFile("item.txt");
    if (!inFile) {
        set_cursor(0, 17);
        print("            Unable to open item.txt for reading            ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }

    ofstream outFile("requestItem.txt", ios::app);
    if (!outFile) {
        set_cursor(0, 17);
        print("            Unable to open requestItem.txt for writing            ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        inFile.close();
        return;
    }

    RequestItem req;
    bool found = false;
    
    while (inFile >> req.itemId >> req.itemName >> req.itemQuan) {
        if (req.itemId == idToBorrow) {
            if(req.itemQuan >= quantity){
                outFile << lastId<< " "<<req.itemId << " " << req.itemName << " " << quantity <<" "<< id<< " "<<
                    name <<" "<< date << endl;
                found = true;    
                set_cursor(0, 17);
                print("            Request for " + to_string(quantity) + " units of " + req.itemName + " has been added            ", 0, {Color::bg_light_green, Color::black});
                Sleep(2000);
            }else{
                set_cursor(0, 17);
                print("      Insufficient stock for " + req.itemName + ". Only " + to_string(req.itemQuan) + " units available      ", 0, {Color::bg_light_red, Color::black});
                Sleep(2000);
                return;
            }
        }
    }

    if (!found) {
        set_cursor(0, 17);
        print("                  Item #" + to_string(idToBorrow) + " not found                  ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
    }

    inFile.close();
    outFile.close();
}


//retorning aytim
void returnItem(int idToReturn) {
    // Open the necessary files
    string dateReturn = getCurrentDate();
    
    ifstream borrowedFile("borrowedItem.txt");
    ifstream itemFile("item.txt");
    ofstream tempItemFile("tempItem.txt", ios::app);
    ofstream tempBorrowedFile("tempBorrowedItem.txt", ios::app);
    ofstream returnRecord("returnRecord.txt", ios::app);

    if (!borrowedFile || !itemFile) {
        set_cursor(0, 17);
        print("      Error Opening Files      ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }

    Item item;
    BorrowedItem borrowedItem;
    bool found = false;

    while (borrowedFile >> borrowedItem.reqId >> borrowedItem.itemId >> borrowedItem.itemName 
                        >> borrowedItem.itemQuan >> borrowedItem.borrowerId >> borrowedItem.borrowerName 
                        >> borrowedItem.borrowDate) {
        if (borrowedItem.reqId == idToReturn) {
            found = true;
            returnRecord << borrowedItem.itemId << " " << borrowedItem.itemName << " "
                        << borrowedItem.itemQuan << " " << borrowedItem.borrowerId << " " << borrowedItem.borrowerName << " "
                        << borrowedItem.borrowDate << " " << dateReturn << endl;
                        
            while (itemFile >> item.id >> item.name >> item.quantity) {
                if (item.id == borrowedItem.itemId) {
                    item.quantity += borrowedItem.itemQuan;
                    tempItemFile << item.id << " " << item.name << " " << item.quantity << endl;
                } else {
                    tempItemFile << item.id << " " << item.name << " " << item.quantity << endl;
                }
            }
            continue;
        } else {
            tempBorrowedFile << borrowedItem.reqId << " " << borrowedItem.itemId << " " 
                           << borrowedItem.itemName << " " << borrowedItem.itemQuan << " "
                           << borrowedItem.borrowerId << " " << borrowedItem.borrowerName << " "
                           << borrowedItem.borrowDate << endl;
        }
    }

    borrowedFile.close();
    itemFile.close();
    tempItemFile.close();
    tempBorrowedFile.close();

    if (found) {
        remove("borrowedItem.txt");
        remove("item.txt");
        rename("tempItem.txt", "item.txt");
        rename("tempBorrowedItem.txt", "borrowedItem.txt");

        set_cursor(0, 17);
        print("      Item #" + to_string(idToReturn) + " Successfully Returned      ", 0, {Color::bg_light_green, Color::black});
        Sleep(2000);
    } else {
        remove("tempItem.txt");
        remove("tempBorrowedItem.txt");
        set_cursor(0, 17);
        print("      Item #" + to_string(idToReturn) + " Not Found in Borrowed List      ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
    }
}

//approbing
void approveRequest(int idToBorrow) {
    string borrowDate = getCurrentDate();
    int toDeduct;

    ifstream inFile("requestItem.txt");
    ifstream inFile2("item.txt");
    if (!inFile || !inFile2) {
        cerr << "Error: Unable to open requestItem.txt or item.txt for reading.\n";
        return;
    }

    ofstream tempFile("temp.txt");
    ofstream tempItemFile("tempItem.txt");
    ofstream borrowedFile("borrowedItem.txt", ios::app);

    if (!tempFile || !tempItemFile || !borrowedFile) {
        set_cursor(0, 17);
        print("      Server Error: Unable to open temp or borrowedItem.txt for writing      ", 0, {Color::bg_light_green, Color::black});
        Sleep(2000);
        return;
    }

    Item item;
    RequestItem req;
    bool found = false;
    bool insufficientStock = false;

    
    while (inFile >> req.reqId >> req.itemId >> req.itemName >> req.itemQuan >> req.borrowerId >> req.borrowerName >> req.date) {
        if (req.reqId == idToBorrow) {
            found = true;

            vector<Item> items;

            while (inFile2 >> item.id >> item.name >> item.quantity) {
                if (item.id == req.itemId) {
                    if (req.itemQuan > item.quantity) {

                        set_cursor(0, 17);
                        print("      Insufficient Stocks      ", 0, {Color::bg_light_green, Color::black});
                        Sleep(2000);

                        insufficientStock = true;
                    } else {
                        toDeduct = item.quantity - req.itemQuan;
                        items.push_back({item.id, item.name, toDeduct});
                    }
                } else {
                    items.push_back(item);
                }
            }

            if (insufficientStock) {
                break;
            }

            
            for (const auto& it : items) {
                tempItemFile << it.id << " " << it.name << " " << it.quantity << endl;
            }

           
            borrowedFile << req.reqId << " " << req.itemId << " " << req.itemName << " " << req.itemQuan << " "
                         << req.borrowerId << " " << req.borrowerName << " " << borrowDate << endl;

        } else {
            
            tempFile << req.reqId << " " << req.itemId << " " << req.itemName << " " << req.itemQuan << " "
                     << req.borrowerId << " " << req.borrowerName << " " << req.date << endl;
        }
    }

    inFile.close();
    inFile2.close();
    tempFile.close();
    tempItemFile.close();
    borrowedFile.close();

    if (found && !insufficientStock) {
        remove("requestItem.txt");
        remove("item.txt");
        rename("temp.txt", "requestItem.txt");
        rename("tempItem.txt", "item.txt");

        set_cursor(0, 17);
        print("      Request ID #" + to_string(idToBorrow) + " Approved!      ", 0, {Color::bg_light_green, Color::black});
        Sleep(2000);

    } else if (found && insufficientStock) {
        remove("temp.txt");
        remove("tempItem.txt");

        set_cursor(0, 17);
        print("        Borrowing failed due to insufficient stocks.        ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);

    } else {
        remove("temp.txt");
        set_cursor(0, 17);
        print("        Request ID " + to_string(idToBorrow) + " not found.        ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
    }
}

void cancelItems(int idToCancel) {
    clearScreen();
	string cancelDate = getCurrentDate();
	
    ifstream inFile("requestItem.txt");
    if (!inFile) {
        cerr << "Error: Unable to open requestItem.txt for reading.\n";
        return;
    }

    ofstream tempFile("temp.txt", ios::app);
    ofstream outFile("cancelItem.txt", ios::app);

    if (!tempFile || !outFile) {
        cerr << "Error: Unable to open file(s) for writing.\n";
        inFile.close();
        return;
    }

    RequestItem req;
    bool found = false;

    while (inFile >>req.reqId>>req.itemId >> req.itemName >> req.itemQuan >>  req.borrowerId >>req.borrowerName >>req.date) {
    if (req.reqId == idToCancel) { 
        outFile << req.reqId<< " "<<req.itemId << " " << req.itemName << " " << req.itemQuan << " "
                << req.borrowerId << " "<<req.borrowerName<<" " << cancelDate << endl;
        found = true;
    } else {
        tempFile<< req.reqId<<" "<<req.itemId << " " << req.itemName << " " << req.itemQuan << " "<<
                  req.borrowerId <<" "<<req.borrowerName<< " " << req.date << endl;
    }
}

    inFile.close();
    outFile.close();
    tempFile.close();

    if (found) {
        remove("requestItem.txt");
        rename("temp.txt", "requestItem.txt");
        cout << "Item with ID " << idToCancel << " has been canceled and removed.\n";
    } else {
        remove("temp.txt"); 
        cout << "Item with ID " << idToCancel << " not found.\n";
    }
}


void readUsers(const bool isdelete) {
    clearScreen();

    bool refetch = false;

    vector<User> users;
    ifstream file("data.txt");
    User user;

    // Read all users into vector
    while (file >> user.id >> user.name >> user.username >> user.password >> user.dept >> user.userAccess) {
        users.push_back(user);
    }
    file.close();

    const int USERS_PER_PAGE = 5;
    int currentPage = 0;
    int totalPages = (users.size() + USERS_PER_PAGE - 1) / USERS_PER_PAGE;
    string command;

    do {

        if(refetch){
            users.clear();
            ifstream file("data.txt");
            User user;

            // Read all users into vector
            while (file >> user.id >> user.name >> user.username >> user.password >> user.dept >> user.userAccess) {
                users.push_back(user);
            }
            file.close();

            refetch = false;
        }

        clearScreen();
        cout << " <<" << string(term_width * 0.40, ' ') << " All Users " << string(term_width * 0.38, ' ') << " >>\n";
        print_gradient(line_str('_'), 35, 40);

        // Display users for current page
        int start = currentPage * USERS_PER_PAGE;
        int end = min(start + USERS_PER_PAGE, (int)users.size());

        for (int i = start; i < end; i++) {
            cout << "\t\t";
            
            cout << Color::cyan;
            cout << left << setw(25) << ("ID: " + to_string(users[i].id));

            cout << Color::yellow;
            cout << setw(25) << ("Name: " + users[i].name);

            cout << Color::white;
            cout << setw(15) << ("Username: " + users[i].username);
            
            space();
            cout << "\t";

            cout << Color::green;
            cout << setw(25) << ("Dept: " + users[i].dept);

            cout << Color::light_red;
            cout << setw(25) << ("Access: " + users[i].userAccess);

            cout << Color::reset;
            space();
            print_gradient(line_str('_'), 35, 40);

            Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        cin >> command;
        if(exit_key(command) || back_key(command)) break;

        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
            continue;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
            continue;
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
            continue;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
            continue;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
            continue;
        }
        else if (tri_left_key(command)) {
            currentPage = 0;
            continue;
        }

        if(isdigit(command[0])){
            deleteUser(stoi(command));
            refetch = true;
            continue;
        }
        else {
            set_cursor(0, 17);
            print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
            Sleep(2000);
        }
    }
    while (!exit_key(command) && !back_key(command));
    clearScreen();
    cin.ignore();
    return;
}

//return all items
void readItems(const bool isDelete) {
    clearScreen();
    bool refetch = false;

    vector<Item> items;
    ifstream file("item.txt");
    Item item;

    // Read all items into vector
    while (file >> item.id >> item.name >> item.quantity) {
        items.push_back(item);
    }
    file.close();

    const int ITEMS_PER_PAGE = 7;
    int currentPage = 0;
    int totalPages = (items.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    string command;

    do {

        if(refetch){
            items.clear();

            ifstream file("item.txt");

            // Read all items into vector
            while (file >> item.id >> item.name >> item.quantity) {
                items.push_back(item);
            }
            file.close();

            refetch = false;
        }

        clearScreen();
        cout << " <<" << string(term_width * 0.40, ' ') <<" All Items " << string(term_width * 0.38, ' ') << " >>\n";
        print_gradient(line_str('_'), 35, 40);

        // Display items for current page
        int start = currentPage * ITEMS_PER_PAGE;
        int end = min(start + ITEMS_PER_PAGE, (int)items.size());

        for (int i = start; i < end; i++) {
            cout << "\t\t";

            setColor(11); // Cyan for ID
            cout << left << setw(20) << ("ID: " + to_string(items[i].id));

            setColor(14); // Yellow for Name
            cout << setw(30) << "Name: " + items[i].name;

            setColor(10); // Green for Quantity
            cout << setw(15) << ("Quantity: " + to_string(items[i].quantity));

            setColor(7);
            space();
            print_gradient(line_str('_'), 35, 40);

            Sleep(15);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        cin >> command;
        if(exit_key(command) || back_key(command)) break;

        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
            continue;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
            continue;
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
            continue;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
            continue;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
            continue;
        }
        else if (tri_left_key(command)) {
            currentPage = 0;
            continue;
        }

        if(isDelete && isdigit(command[0])){
            deleteItem(stoi(command));
            refetch = true;
            continue;
        }

        set_cursor(0, 17);
        print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
    }
    while (!exit_key(command) && !back_key(command));
    clearScreen();
    cin.ignore();
    return;
}

//changing password
void changePass(int id, string confirmedPass){
    ifstream file("data.txt"); 
    ofstream temp("tempData.txt",ios::app );
    User user;
    if (file.is_open()) {
        while (file >> user.id >> user.name >> user.username >> user.password >> user.dept>> user.userAccess) {
            if(id == user.id){
                temp <<user.id<<" "<< user.name<<" "<< user.username<<" "<< confirmedPass<<" "<< user.dept<<" "<<user.userAccess<<endl;
            }else{
                temp <<user.id<<" "<< user.name<<" "<< user.username<<" "<< user.password<<" "<< user.dept<<" "<<user.userAccess<<endl;
            }
        }
        
        file.close();
        temp.close();
    }
    
    remove("data.txt");
    rename("tempData.txt","data.txt");
}
        
// show returned Itemsss
void readReturnItems() {
    clearScreen();
    vector<ReturnedItem> returns;
    ifstream file("returnRecord.txt");
    ReturnedItem returned;

    // Read all returns into vector
    while (file >> returned.itemId >> returned.itemName >> returned.itemQuan >> 
           returned.borrowerId >> returned.borrowerName >> returned.borrowDate >> returned.dateReturn) {
        returns.push_back(returned);
    }
    file.close();

    const int RETURNS_PER_PAGE = 3;
    int currentPage = 0;
    int totalPages = (returns.size() + RETURNS_PER_PAGE - 1) / RETURNS_PER_PAGE;
    string command;

    do {
        clearScreen();
        // Display returns for current page
        int start = currentPage * RETURNS_PER_PAGE;
        int end = min(start + RETURNS_PER_PAGE, (int)returns.size());

        for (int i = start; i < end; i++) {
            cout << Color::bg_light_magenta << Color::bold;
            cout << " Return Record #" + to_string(returns[i].itemId) << string(39 - to_string(returns[i].itemId).length() + 1, ' ') << "Return Date: " + returns[i].dateReturn << " ";
            cout << Color::reset;
            space(2);

            cout << "\t";
            cout << Color::cyan;
            cout << left << setw(20) << ("Item ID: " + to_string(returns[i].itemId));
            
            cout << Color::yellow;
            cout << setw(25) << ("Item: " + returns[i].itemName);
            
            cout << Color::light_magenta;
            cout << setw(15) << ("Qty: " + to_string(returns[i].itemQuan));
            
            space();
            cout << "\t";
            
            cout << Color::light_green;
            cout << left << setw(20) << ("Account ID: " + to_string(returns[i].borrowerId));
            
            cout << Color::white;
            cout << setw(25) << ("Borrower: " + returns[i].borrowerName);
            
            cout << Color::light_blue;
            cout << setw(15) << ("Borrow Date: " + returns[i].borrowDate);
            
            space(2);
            cout << Color::reset;
            print_line('_', Color::bg_light_magenta + Color::black);
            Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        getline(cin, command);

        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
        }
        else if (tri_left_key(command)) {
            currentPage = 0;
        }
        else if (!exit_key(command) && !back_key(command)) {
            set_cursor(0, 17);
            print("      Invalid Command      ", 0, {Color::bg_red, Color::white});
            Sleep(2000);
        }
    }
    while (!exit_key(command) && !back_key(command));
    clearScreen();
    return;
} 

//user's all requests only
void readMyRequest(int id) {
    clearScreen();
    cout << "Pending Request" << endl;
    
    ifstream file("requestItem.txt");
    RequestItem req;
    
    if (file.is_open()) {
        while (file >> req.reqId>> req.itemId >> req.itemName >> req.itemQuan 
                     >> req.borrowerId >> req.borrowerName>> req.date) {
            if (id == req.borrowerId) {
                cout << "Req. ID: " << req.reqId
					 << ", Item ID: " << req.itemId 
                     << ", Item Name: " << req.itemName 
                     << ", Quantity: " << req.itemQuan 
                     << ", Date: " << req.date << endl;
            }
        }
        file.close(); 
    } else {
        cout << "Failed to open requestItem.txt" << endl;
    }
    
    cout << "--------------------------------" << endl;
}
void readMyBorrow(int id) {
    clearScreen();
    vector<BorrowedItem> borrows;
    ifstream file("borrowedItem.txt");
    BorrowedItem borrow;
    bool refetch = false;

    // Read all borrows into vector
    while (file >> borrow.reqId >> borrow.itemId >> borrow.itemName 
        >> borrow.itemQuan >> borrow.borrowerId >> borrow.borrowerName >> borrow.borrowDate) {
        if(borrow.borrowerId == id) {
         borrows.push_back(borrow);
        }
    }
    file.close();

    const int BORROWS_PER_PAGE = 5;
    int currentPage = 0;
    int totalPages = (borrows.size() + BORROWS_PER_PAGE - 1) / BORROWS_PER_PAGE;
    string command;

    do {
        if(refetch) {
            borrows.clear();
            ifstream file("borrowedItem.txt");
            
            while (file >> borrow.reqId >> borrow.itemId >> borrow.itemName 
                >> borrow.itemQuan >> borrow.borrowerId >> borrow.borrowerName >> borrow.borrowDate) {
                if(borrow.borrowerId == id) {
                    borrows.push_back(borrow);
                }
            }
            file.close();

            totalPages = (borrows.size() + BORROWS_PER_PAGE - 1) / BORROWS_PER_PAGE;
            if(currentPage >= totalPages) {
                currentPage = max(0, totalPages - 1);
            }
            refetch = false;
        }

        clearScreen();
        cout << " <<" << string(term_width * 0.39, ' ') << " My Borrows " << string(term_width * 0.37, ' ') << " >>\n";
        print_gradient(line_str('_'), 35, 40);

        // Display borrows for current page
        int start = currentPage * BORROWS_PER_PAGE;
        int end = min(start + BORROWS_PER_PAGE, (int)borrows.size());

        for (int i = start; i < end; i++) {
         cout << "\t\t";
         
         cout << Color::cyan;
         cout << left << setw(20) << ("Borrow ID: " + to_string(borrows[i].reqId));
         
         cout << Color::yellow;
         cout << setw(25) << ("Item: " + borrows[i].itemName);
         
         cout << Color::light_magenta;
         cout << setw(15) << ("Qty: " + to_string(borrows[i].itemQuan));
         
         space();
         cout << "\t";
         
         cout << Color::green;
         cout << setw(20) << ("Item ID: " + to_string(borrows[i].itemId));
         
         cout << Color::light_red;
         cout << setw(25) << ("Date: " + borrows[i].borrowDate);

         cout << Color::reset;
         space();
         print_gradient(line_str('_'), 35, 40);
         Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        getline(cin, command);

        if(exit_key(command) || back_key(command)) break;

        // Handle return command
        if(convert_case(command, "lower").substr(0,6) == "return") {
            string idStr = command.substr(7);
            if(isdigit(idStr[0])) {
                int returnId = stoi(idStr);
                bool validId = false;
                
                // Verify the return ID belongs to this user
                for(const auto& b : borrows) {
                    if(b.reqId == returnId) {
                        validId = true;
                        break;
                    }
                }

                if(validId) {
                    returnItem(returnId);
                    refetch = true;
                    continue;
                } else {
                    set_cursor(0, 17);
                    print("      Invalid Borrow ID      ", 0, {Color::bg_light_red, Color::black});
                    Sleep(2000);
                    continue;
                }
            }
        }

        // Handle navigation
        if (right_key(command)) {
         if (currentPage < totalPages - 1) currentPage++;
        }
        else if (db_right_key(command)) {
         currentPage = min(currentPage + 2, totalPages - 1);
        }
        else if (tri_right_key(command)) {
         currentPage = totalPages - 1;
        }
        else if (left_key(command)) {
         if (currentPage > 0) currentPage--;
        }
        else if (db_left_key(command)) {
         currentPage = max(currentPage - 2, 0);
        }
        else if (tri_left_key(command)) {
         currentPage = 0;
        }
        else {
         set_cursor(0, 17);
         print("      Invalid Command      ", 0, {Color::bg_red, Color::white});
         Sleep(2000);
        }
    } while(true);
}
//admin side
void readAllUserRequest() {
    clearScreen();
    vector<RequestItem> requests;
    ifstream file("requestItem.txt");
    RequestItem req;

    // Read all requests into vector
    while (file >> req.reqId >> req.itemId >> req.itemName 
           >> req.itemQuan >> req.borrowerId >> req.borrowerName >> req.date) {
        requests.push_back(req);
    }
    file.close();

    const int REQUESTS_PER_PAGE = 3;
    int currentPage = 0;
    int totalPages = (requests.size() + REQUESTS_PER_PAGE - 1) / REQUESTS_PER_PAGE;
    string command;
    bool refetch = false;

    do {
        if(refetch){
            requests.clear();
            ifstream file("requestItem.txt");

            // Read all requests into vector
            while (file >> req.reqId >> req.itemId >> req.itemName 
                >> req.itemQuan >> req.borrowerId >> req.borrowerName >> req.date) {
                requests.push_back(req);
            }
            file.close();

            currentPage = 0;
            totalPages = (requests.size() + REQUESTS_PER_PAGE - 1) / REQUESTS_PER_PAGE;
            refetch = false;
        }

        clearScreen();
        // Display requests for current page
        int start = currentPage * REQUESTS_PER_PAGE;
        int end = min(start + REQUESTS_PER_PAGE, (int)requests.size());

        for (int i = start; i < end; i++) {
            
            line_title("Request ID: #" + to_string(requests[i].reqId), ' ', Color::bg_light_yellow, Color::black);

            space();
            cout << "\t";
            cout << Color::cyan;
            cout << left << setw(20) << ("Item ID: " + to_string(requests[i].itemId));
            
            cout << Color::yellow;
            cout << setw(25) << ("Item: " + requests[i].itemName);
            
            cout << Color::light_magenta; 
            cout << setw(15) << ("Qty: " + to_string(requests[i].itemQuan));
            
            space();
            cout << "\t";
            
            cout << Color::light_green;
            cout << left << setw(20) << ("Account ID: " + to_string(requests[i].borrowerId));

            cout << Color::white;
            cout << setw(25) << ("Borrower: " + requests[i].borrowerName);
            
            cout << Color::light_red;
            cout << setw(15) << ("Date: " + requests[i].date);

            cout << Color::reset;
            space(2);
            print_line('_', Color::bg_light_yellow + Color::black);
            Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        cin >> command;

        // EXIT
        if(exit_key(command) || back_key(command)) break;

        if(isdigit(command[0])) { 
            int reqId = stoi(command);
            ifstream checkFile("requestItem.txt");
            RequestItem req;
            bool found = false;

            while (checkFile >> req.reqId >> req.itemId >> req.itemName >> req.itemQuan 
                   >> req.borrowerId >> req.borrowerName >> req.date) {
                if (req.reqId == reqId) {
                    found = true;
                    break;
                }
            }
            checkFile.close();

            if(found) {
                approveRequest(reqId);
                refetch = true;
                continue;

            } else {
                set_cursor(0, 17);
                print("      Invalid Request ID      ", 0, {Color::bg_red, Color::white});
                Sleep(2000); 
                continue;
            }
        }
        
        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
        }
        else if (tri_left_key(command)) {
            currentPage = 0;
        }
        else{
            set_cursor(0, 17);
            print("      Invalid Command      ", 0, {Color::bg_red, Color::white});
            Sleep(2000);
        }
        
    }
    while (!exit_key(command) && !back_key(command));
    clearScreen();
    cin.ignore();
    return;
}

void readAllBorrowedItem(){
    clearScreen();
    vector<BorrowedItem> borrows;
    ifstream file("borrowedItem.txt");
    BorrowedItem borrow;

    // Read all borrowed items into vector 
    while (file >> borrow.reqId >> borrow.itemId >> borrow.itemName 
           >> borrow.itemQuan >> borrow.borrowerId >> borrow.borrowerName >> borrow.borrowDate) {
        borrows.push_back(borrow);
    }
    file.close();

    const int BORROWS_PER_PAGE = 3;
    int currentPage = 0;
    int totalPages = (borrows.size() + BORROWS_PER_PAGE - 1) / BORROWS_PER_PAGE;
    string command;
    bool refetch = false;

    do {
        if(refetch) {
            borrows.clear();
            ifstream file("borrowedItem.txt");
            
            while (file >> borrow.reqId >> borrow.itemId >> borrow.itemName 
                   >> borrow.itemQuan >> borrow.borrowerId >> borrow.borrowerName >> borrow.borrowDate) {
                borrows.push_back(borrow);
            }
            file.close();

            currentPage = 0;
            totalPages = (borrows.size() + BORROWS_PER_PAGE - 1) / BORROWS_PER_PAGE;
            refetch = false;
        }

        clearScreen();
        // Display borrowed items for current page
        int start = currentPage * BORROWS_PER_PAGE;
        int end = min(start + BORROWS_PER_PAGE, (int)borrows.size());

        for (int i = start; i < end; i++) {
            line_title("Request ID: #" + to_string(borrows[i].reqId), ' ', Color::bg_light_cyan, Color::black);

            space();
            cout << "\t";
            cout << Color::cyan;
            cout << left << setw(20) << ("Item ID: " + to_string(borrows[i].itemId));
            
            cout << Color::yellow;
            cout << setw(25) << ("Item: " + borrows[i].itemName);
            
            cout << Color::light_magenta;
            cout << setw(15) << ("Qty: " + to_string(borrows[i].itemQuan));
            
            space();
            cout << "\t";
            
            cout << Color::light_green;
            cout << left << setw(20) << ("Account ID: " + to_string(borrows[i].borrowerId));
            
            cout << Color::white;
            cout << setw(25) << ("Borrower: " + borrows[i].borrowerName);
            
            cout << Color::light_red;
            cout << setw(15) << ("Date: " + borrows[i].borrowDate);

            cout << Color::reset;
            space(2);
            print_line('_', Color::bg_light_cyan + Color::black);
            Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        cin >> command;

        if(isdigit(command[0])) {
            int reqId = stoi(command);
            ifstream checkFile("borrowedItem.txt");
            BorrowedItem borrow;
            bool found = false;

            while (checkFile >> borrow.reqId >> borrow.itemId >> borrow.itemName 
                   >> borrow.itemQuan >> borrow.borrowerId >> borrow.borrowerName >> borrow.borrowDate) {
                if (borrow.reqId == reqId) {
                    found = true;
                    break;
                }
            }
            checkFile.close();

            if(found) {
                returnItem(reqId);
                refetch = true;
                continue;
            } else {
                set_cursor(0, 17);
                print("      Invalid Request ID      ", 0, {Color::bg_red, Color::white});
                Sleep(2000);
                continue;
            }
        }

        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
        }
        else if (tri_left_key(command)) {
            currentPage = 0;  
        }
        else if (!exit_key(command) && !back_key(command)) {
            set_cursor(0, 17);
            print("      Invalid Command      ", 0, {Color::bg_red, Color::white});
            Sleep(2000);
        }
    }
    while (!exit_key(command) && !back_key(command));
    clearScreen();
    cin.ignore();
    return;
}
//user's all cancelled items only
void readMyCancelled(int id) {
    clearScreen();
    vector<RequestItem> cancelled_items;
    ifstream file("cancelItem.txt");
    RequestItem cancelled;

    // Read all cancelled items into vector
    while (file >> cancelled.reqId >> cancelled.itemId >> cancelled.itemName 
           >> cancelled.itemQuan >> cancelled.borrowerId >> cancelled.borrowerName >> cancelled.date) {
        if(cancelled.borrowerId == id) {
            cancelled_items.push_back(cancelled);
        }
    }
    file.close();

    const int ITEMS_PER_PAGE = 5;
    int currentPage = 0;
    int totalPages = (cancelled_items.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
    string command;

    do {
        clearScreen();
        cout << " <<" << string(term_width * 0.35, ' ') << " My Cancellation  " << string(term_width * 0.34, ' ') << " >>\n";
        print_gradient(line_str('_'), 35, 40);

        // Display cancelled items for current page
        int start = currentPage * ITEMS_PER_PAGE;
        int end = min(start + ITEMS_PER_PAGE, (int)cancelled_items.size());

        for (int i = start; i < end; i++) {
            cout << "\t\t";
            
            cout << Color::cyan;
            cout << left << setw(20) << ("Request ID: " + to_string(cancelled_items[i].reqId));
            
            cout << Color::yellow;
            cout << setw(25) << ("Item: " + cancelled_items[i].itemName);
            
            cout << Color::light_magenta;
            cout << setw(15) << ("Qty: " + to_string(cancelled_items[i].itemQuan));
            
            space();
            cout << "\t";
            
            cout << Color::green;
            cout << setw(20) << ("Item ID: " + to_string(cancelled_items[i].itemId));
            
            cout << Color::light_red;
            cout << setw(25) << ("Date: " + cancelled_items[i].date);

            cout << Color::reset;
            space();
            print_gradient(line_str('_'), 35, 40);
            Sleep(30);
        }

        space(2);
        print("Command: ", -28);
        print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
        cout << "\033[54D";
        getline(cin, command);

        if(exit_key(command) || back_key(command)) break;

        // Handle navigation
        if (right_key(command)) {
            if (currentPage < totalPages - 1) currentPage++;
        }
        else if (db_right_key(command)) {
            currentPage = min(currentPage + 2, totalPages - 1);
        }
        else if (tri_right_key(command)) {
            currentPage = totalPages - 1;
        }
        else if (left_key(command)) {
            if (currentPage > 0) currentPage--;
        }
        else if (db_left_key(command)) {
            currentPage = max(currentPage - 2, 0);
        }
        else if (tri_left_key(command)) {
            currentPage = 0;
        }
        else {
            set_cursor(0, 17);
            print("      Invalid Command      ", 0, {Color::bg_red, Color::white});
            Sleep(2000);
        }
    } while (!exit_key(command) && !back_key(command));
    clearScreen();
    return;
}

//deleting user(admin side)
void deleteUser(int idToDelete) {
    ifstream inFile("data.txt");
    if (!inFile) {
        set_cursor(0, 17);
        print("      Unable to open data.txt for reading      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }

    ofstream outFile("temp.txt");
    if (!outFile) {
        set_cursor(0, 17);
        print("      Unable to open temp.txt for writing      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        inFile.close();
        return;
    }

    User user;
    bool found = false;

   	while (inFile >> user.id >> user.name >> user.username >> user.password >> user.dept >> user.userAccess) {
	    if (user.id == idToDelete) {
	        if (user.userAccess == "admin" || user.userAccess == "ADMIN" || user.userAccess == "Admin") {
                set_cursor(0, 17);
                print("      Can't delete Admin user      \n", 0, {Color::bg_light_red, Color::black});
                Sleep(2000);
	            return;
	        }
	        found = true; 
	    } else {
	        outFile << user.id << " " << user.name << " " << user.username << " "
	                << user.password << " " << user.dept << " " << user.userAccess << endl;
	    }
	}


    inFile.close();
    outFile.close();
    
	ifstream check("data.txt");
	check.close();
	if (check.is_open()) {
        set_cursor(0, 17);
        print("      data.txt is still open somehow before remove()      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
	} else {
        set_cursor(0, 17);
        print("      data.txt appears to be closed      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
	}
	check.close();
	
    if (found) {
    
    if (remove("data.txt") != 0) {
        set_cursor(0, 17);
        print("      Error deleting original data file      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }
    
    if (rename("temp.txt", "data.txt") != 0) {
        set_cursor(0, 17);
        print("      Error renaming temp file to data.txt      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }
    cout << ".\n";
    set_cursor(0, 17);
    print("                  User deleted successfully                  \n", 0, {Color::bg_green, Color::black});
    Sleep(2000);
}
	 else {
        set_cursor(0, 17);
        print("      User not found      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        if (remove("temp.txt") != 0) {
            set_cursor(0, 17);
            print("      Error deleting temporary file      \n", 0, {Color::bg_light_red, Color::black});
            Sleep(2000);
        }
    }
}
//deleting item(admin side)
void deleteItem(int idToDelete) {

    ifstream inFile("item.txt");
    if (!inFile) {
        set_cursor(0, 17);
        print("      Server Error: Unable to open data.txt for reading      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }

    ofstream outFile("tempItem.txt");
    if (!outFile) {
        set_cursor(0, 17);
        print("      Server Error: Unable to open temp.txt for writing      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        inFile.close();
        return;
    }

    Item item;
    bool found = false;

    while (inFile >> item.id >> item.name >> item.quantity ) {
        if (item.id != idToDelete) {
            outFile << item.id << " " << item.name << " " << item.quantity << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();
    
	ifstream check("item.txt");
	check.close();
	if (check.is_open()) {
        set_cursor(0, 17);
        print("      item.txt is still open somehow before remove()      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
	} else {
        set_cursor(0, 17);
        print("      item.txt appears to be closed      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
	}
	check.close();
	
    if (found) {
    if (remove("item.txt") != 0) {
        set_cursor(0, 17);
        print("      Error deleting original data file      \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }
    if (rename("tempItem.txt", "item.txt") != 0) {
        set_cursor(0, 17);
        print("      Error renaming temp file to data.txt      ", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);
        return;
    }
    set_cursor(0, 17);
    print("                  Item deleted successfully                  ", 0, {Color::bg_green, Color::black});
    Sleep(2000);
}
	 else {
        set_cursor(0, 17);
        print("            Item not found            \n", 0, {Color::bg_light_red, Color::black});
        Sleep(2000);

        if (remove("temp.txt") != 0) {
            set_cursor(0, 17);
            print("      Error deleting temporary file      \n", 0, {Color::bg_light_red, Color::black});
            Sleep(2000);
        }
    }
}


//asking for inputs
bool userExists(const string& username) {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open data.txt\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, name, storedUsername, password, dept, userAccess;

        getline(ss, idStr, ' ');      
        getline(ss, name, ' ');          
        getline(ss, storedUsername, ' ');
        getline(ss, password, ' ');       
        getline(ss, dept, ' ');            
        getline(ss, userAccess, ' ');     

        if (storedUsername == username) {
            return true;
        }
    }

    return false;
}

void registerUser() {
    system("cls");

    User user;
    user.id = getLastUserId() + 1;

    // UI Configuration
    char symbol = '_';
    int delay = 2500;
    int gradient[] = {89, 93};
    string input_box_pos = "left";

    do{
       
        // DISPLAY PAGE
        print_gradient(line_str(symbol), gradient[0], gradient[1]);
        space(3);
        
        // PROMPT
        print("S I G N  U P");
        space(2);
        print_input_box(20, 0, Config::color_theme, "firstname", false, input_box_pos);
        space(2);
        print_input_box(20, 0, Config::color_theme, "username", false, input_box_pos);
        space(2);
        print_input_box(20, 0, Config::color_theme, "password", false, input_box_pos);

        space(2);
        print_gradient(line_str(symbol), gradient[0], gradient[1]);
        cout.flush();

        // Exit Controls
        string control_color = Color::gray;

        cout << control_color << "\nExit: \e" << "\e[0m";
        for(string key : exit_keybinds()){
            cout << control_color << key <<  " \e[0m";
        }
        cout << "\r";

        // Back Controls
        cout << control_color << "\nReset: \e" << "\e[0m";
        for(string key : back_keybinds()){
            cout << control_color << key <<  " \e[0m";
        }
        cout << "\r";

        
        // FIRST NAME
        set_cursor(31, 6);
        std::cin.clear();
        if (cin.peek() == '\n') cin.ignore();
        getline(cin, user.name);
        if(exit_key(user.name)) return;
        if(back_key(user.name)){
            system("cls");
            continue;
        }
        if (user.name.find(' ') != string::npos) {
            set_cursor(0, 19);
            print("  Please use '-' for multiple names  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls");
            continue;
        }
        cout.flush();

        // USERNAME
        set_cursor(31, 10);
        getline(cin, user.username);
        if(exit_key(user.username)) return;
        if(back_key(user.username)){
            system("cls");
            continue;
        }
        if (user.username.find(' ') != string::npos) {
            set_cursor(0, 19);
            print("  Please use '-' for multiple names  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls");
            continue;
        }
        if (userExists(user.username)) {
            set_cursor(0, 19);
            print("  Username already exist  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls");
            continue;
        }
        cout.flush();


        set_cursor(31, 14);
        getline(cin, user.password);
        if(exit_key(user.password)) return;
        if(back_key(user.password)){
            system("cls");
            continue;
        }
        if (user.password.find(' ') != string::npos) {
            set_cursor(0, 19);
            print("  Cannot add spaces to your password (use '-')  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls");
            continue;
        }

        system("cls");

        // DISPLAY PAGE 2
        print_gradient(line_str(symbol), gradient[0], gradient[1]);
        space(4);
        
        // PROMPT
        print("U S E R - T Y P E");
        space(3);
        print_input_box(20, 0, Config::color_theme, "department", false, input_box_pos);
        space(2);
        print_input_box(20, 0, Config::color_theme, "access-control", false, input_box_pos);
        space(4);
        print_gradient(line_str(symbol), gradient[0], gradient[1]);

        // Exit Controls
        cout << control_color << "\nExit: \e" << "\e[0m";
        for(string key : exit_keybinds()){
            cout << control_color << key <<  " \e[0m";
        }
        cout << "\r";
        
        // Back Controls
        cout << control_color << "\nReset: \e" << "\e[0m";
        for(string key : back_keybinds()){
            cout << control_color << key <<  " \e[0m";
        }
        cout << "\r";

        cout.flush();

        set_cursor(31, 8);
        getline(cin, user.dept);
        if(exit_key(user.dept)) return;
        if(back_key(user.dept)){
            system("cls");
            continue;
        }
        if (user.dept.find(' ') != string::npos) {
            set_cursor(0, 19);
            print("  Cannot add spaces to your Department (use '-')  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls");
            continue;
        }

        set_cursor(31, 12);
        getline(cin, user.userAccess);
        if(exit_key(user.userAccess)) return;
        if(back_key(user.userAccess)){
            system("cls");
            continue;
        }
        string access = convert_case(user.userAccess, "lower");
        if(access != "admin" && access != "user") {
            set_cursor(0, 19);
            print("  Access control must be 'admin' or 'user'  ", 0, {Color::bg_red});
            Sleep(delay);
            system("cls"); 
            continue;
        }

        // Commit Transaction
        addUser(user);

        space(2);
        print("      Registration successful!      ", 0, { Color::bg_blue });
        Sleep(3000);
        system("cls");
        return;
    }
    while(true);
}

//Admin dashboard nakalagay naman HAHAHAH
void adminDashboard(int id,string name ,string username, string department, string userAccess,string password) {
	clearScreen();
    string choice;  // Initializings
    Item item;

    do{
        clearScreen();

        print_gradient(line_str('='), 203, 207);

        print_triple_text("Name: " + name + "(" + username + ")", "Access: " + userAccess, "Department: " + department, 2);
 
        print_gradient(line_str('='), 203, 207);
        
        space(2);
        print_gradient("ADMIN DASHBOARD", 221, 223);
        space(2);

        print_triple_input_box("Show Items", "Show Users", "Add Item", 20, 3, 1, Color::light_yellow);
        space();
        print_triple_input_box("Borrow Request", "Borrowed Items", "Returned Items", 20, 3, 1, Color::light_yellow);
        space();
        print_triple_input_box("Delete Item", "Delete User", "Account Settings", 20, 3, 1, Color::light_yellow);
        space(2);
        print_gradient(line_str('='), 203, 207);
        space(1);
        
        print_input_box(20, 0, Config::color_theme, "command", false);
        set_cursor(31, 18);

        getline(cin, choice);

        if(show_items_key(choice)) {
            clearScreen();
            readItems();
            continue;
        }

        else if(show_users_key(choice)) {
            clearScreen(); 
            readUsers();
            continue;
        }

        else if(add_item_key(choice)) {

            do{
                clearScreen();
                    
                space();
                line_title("Adding Item", '=', Color::light_cyan, Color::yellow);
                space();
                
                item.id = getLastItemId() + 1;
                
                print_label_box("ID: #00" + to_string(item.id), 78, -1, Color::light_yellow, Color::black, Color::bg_white);
                space(2);
                print_input_box(20, 0, Color::white, "name", false);
                space(2);
                print_input_box(20, 0, Color::white, "quantity", false);

                space(2);
                print_line('=', Color::light_cyan);
                space();

                // Exit Key
                cout << Color::gray << "\nExit: " << "\e[0m";
                for(string key : exit_keybinds()){
                    cout << Color::gray << key <<  " \e[0m";
                }
                
                // Back Key
                cout << Color::gray << "\nReset: " << "\e[0m";
                for(string key : back_keybinds()){
                    cout << Color::gray << key <<  " \e[0m";
                }

                set_cursor(31, 8);
                getline(cin, item.name);
                if(exit_key(item.name)) break;
                if(back_key(item.name)) continue;
                
                set_cursor(31, 12);
                string quantityStr;
                getline(cin, quantityStr);
                if(exit_key(quantityStr)) break;
                if(back_key(quantityStr)) continue;

                set_cursor(0, 17);
                print("           Adding Item           ", 0, {Color::bg_cyan, Color::black});
                Sleep(2000);

                // Check for spaces in name
                if(item.name.find(' ') != string::npos) {
                    set_cursor(0, 17); 
                    print("  Use dash '-' for multiple words  ", 0, {Color::bg_light_red, Color::black});
                    Sleep(3000);
                    continue;
                }

                // Check for numbers in name
                bool hasNumber = false;
                for(char c : item.name) {
                    if(isdigit(c)) {
                        hasNumber = true;
                        break;
                    }
                }
                if(hasNumber) {
                    set_cursor(0, 17);
                    print("  Item name cannot contain numbers  ", 0, {Color::bg_light_red, Color::black});
                    Sleep(3000);
                    continue;
                }

                // Check if quantity is a number
                bool isNumber = true;
                for(char c : quantityStr) {
                    if(!isdigit(c)) {
                        isNumber = false;
                        break;
                    }
                }
                if(!isNumber) {
                    set_cursor(0, 17);
                    print("    Quantity must be a number    ", 0, {Color::bg_light_red, Color::black});
                    Sleep(3000);
                    continue;
                }
                
                item.quantity = stoi(quantityStr);

                Sleep(3000);

                // RERENDER PAGE
                clearScreen();
                space();
                line_title("Adding Item", '=', Color::light_cyan, Color::yellow);
                space();
                
                item.id = getLastItemId() + 1;
                
                print_label_box("ID: #00" + to_string(item.id), 78, -1, Color::yellow, Color::black, Color::bg_light_green);
                space(2);
                print_input_box(20, 0, Color::white, "name", false);
                space(2);
                print_input_box(20, 0, Color::white, "quantity", false);
                
                space(2);
                print_line('=', Color::light_cyan);
                space();

                // Exit Key
                cout << Color::gray << "\nExit: " << "\e[0m";
                for(string key : exit_keybinds()){
                    cout << Color::gray << key <<  " \e[0m";
                }
                
                // Back Key
                cout << Color::gray << "\nReset: " << "\e[0m";
                for(string key : back_keybinds()){
                    cout << Color::gray << key <<  " \e[0m";
                }
                
                set_cursor(31, 8);
                cout << item.name;
                set_cursor(31, 12);
                cout << item.quantity;
                set_cursor(0, 17);
                print("     Item Added Successfully     ", 0, {Color::bg_bright_green, Color::black});
                addItem(item);
                Sleep(3000);
                break;
            }
            while(true);
            
            continue;
        }

        else if(borrow_request_key(choice)) {

            readAllUserRequest();
            continue;
        } 

        else if(borrowed_items_key(choice)) {

            readAllBorrowedItem();
            continue;
        }

        else if(returned_items_key(choice)) {

            readReturnItems();
            continue;
        }

        else if(delete_items_key(choice)) {

            readItems(true);
            continue;

        }

        else if(delete_user_key(choice)) {

            readUsers(true);   
            continue;

        }

        else if(account_settings_key(choice)) {

            do {
                clearScreen();
                
                space(4);
                line_title("Account Settings", '=', Color::light_cyan, Color::yellow);
                space(2);

                print_triple_input_box("Change Password", "Logout", "Back", 20, 3, 1, Color::light_yellow);
                space(2);
                print_line('=', Color::light_cyan);
                space(4);
                
                print_input_box(20, 0, Config::color_theme, "command", false);
                set_cursor(31, 16);
                
                string settingsChoice;
                getline(cin, settingsChoice);

                if(exit_key(settingsChoice) || back_key(settingsChoice)) break;

                if(change_password_key(settingsChoice)) {
                    clearScreen();
                    
                    space(2);
                    line_title("Change Password", '=', Color::light_cyan, Color::yellow);
                    space();
                    
                    print_input_box(20, 0, Color::white, "current password", false);
                    space(2);
                    print_input_box(20, 0, Color::white, "new password", false); 
                    space(2);
                    print_input_box(20, 0, Color::white, "confirm password", false);

                    space(2);
                    print_line('=', Color::light_cyan);
                    space();

                    set_cursor(31, 5);
                    string currentPass;
                    getline(cin, currentPass);
                    if(exit_key(currentPass) || back_key(currentPass)) continue;

                    set_cursor(31, 9);  
                    string newPass;
                    getline(cin, newPass);
                    if(exit_key(newPass) || back_key(newPass)) continue;

                    set_cursor(31, 13);
                    string confirmPass;
                    getline(cin, confirmPass);
                    if(exit_key(confirmPass) || back_key(confirmPass)) continue;

                    if(currentPass == password){
                        if(newPass == confirmPass){
                            changePass(id, confirmPass);
                            set_cursor(0, 18);
                            print("      Password Changed Successfully      ", 0, {Color::bg_light_green, Color::black});
                            Sleep(2000);
                        }
                        else{
                            set_cursor(0, 18);
                            print("      Passwords Do Not Match      ", 0, {Color::bg_light_red, Color::black});
                            Sleep(2000);
                        }
                    }
                    else{
                        set_cursor(0, 18);
                        print("      Current Password Is Incorrect      ", 0, {Color::bg_light_red, Color::black});
                        Sleep(2000);
                    }
                }
                else if(logout_key(settingsChoice)) {

                    // Logout Animation
                    clearScreen();

                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out           ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out .         ", 0, {Color::bg_white, Color::black}); 
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out . .       ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8); 
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out . . .     ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 84, 87, true);
                    space(2);
                    print("      Successfully logged out!      ", 0, {Color::bg_bright_green, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 84, 87, true);
                    space(7);
                    Sleep(3000);

                    clearScreen();

                    return;
                }
                else {
                    set_cursor(0, 13);
                    print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
                    Sleep(2000);
                }
            } 
            while(true);
            continue;
        }

        else if(exit_key(choice) || back_key(choice)) {

            // Logout Animation
            clearScreen();

            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out           ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out .         ", 0, {Color::bg_white, Color::black}); 
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out . .       ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8); 
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out . . .     ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 84, 87, true);
            space(2);
            print("      Successfully logged out!      ", 0, {Color::bg_bright_green, Color::black});
            space(2);
            print_gradient(line_str(' '), 84, 87, true);
            space(7);
            Sleep(3000);

            clearScreen();
            return;
        }

        else {

            cout << "Invalid input.\n";
            Sleep(2500); 
            system("cls");
            continue;

        }
    }
    while(!exit_key(choice) || !back_key(choice));
    return;
}

void userDashboard(int id, string name, string username, string department, string userAccess, string password) {
    clearScreen();
    string choice;
    string date = getCurrentDate();

    do {
        clearScreen();
        
        print_gradient(line_str('='), 221, 225);

        print_triple_text("Name: " + name + "(" + username + ")", "Access: " + userAccess, "Department: " + department, 2);
 
        print_gradient(line_str('='), 221, 225);
        
        space(2);
        print_gradient("USER DASHBOARD", 221, 223);
        space(2);

        print_triple_input_box("Show Items", "My Requests", "My Borrows", 20, 3, 1, Color::light_yellow);
        space();
        print_triple_input_box("My Cancellations", "Account Settings", "Back", 20, 3, 1, Color::light_yellow);
        space(2);
        print_gradient(line_str('='), 221, 225);
        space(2);
        
        print_input_box(20, 0, Config::color_theme, "command", false);
        set_cursor(31, 16);
        
        getline(cin, choice);

        if(show_items_key(choice)) {
            clearScreen();
            bool refetch = false;

            vector<Item> items;
            ifstream file("item.txt");
            Item item;

            // Read all items into vector
            while (file >> item.id >> item.name >> item.quantity) {
                items.push_back(item);
            }
            file.close();

            const int ITEMS_PER_PAGE = 7;
            int currentPage = 0;
            int totalPages = (items.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
            string command;

            do {

                if(refetch){
                    items.clear();

                    ifstream file("item.txt");

                    // Read all items into vector
                    while (file >> item.id >> item.name >> item.quantity) {
                        items.push_back(item);
                    }
                    file.close();

                    totalPages = (items.size() + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;
                    if(currentPage > totalPages){
                        currentPage = currentPage - 1;
                    }

                    refetch = false;
                }

                clearScreen();
                cout << " <<" << string(term_width * 0.40, ' ') <<" All Items " << string(term_width * 0.38, ' ') << " >>\n";
                print_gradient(line_str('_'), 35, 40);

                // Display items for current page
                int start = currentPage * ITEMS_PER_PAGE;
                int end = min(start + ITEMS_PER_PAGE, (int)items.size());

                for (int i = start; i < end; i++) {
                    cout << "\t\t";

                    setColor(11); // Cyan for ID
                    cout << left << setw(20) << ("ID: " + to_string(items[i].id));

                    setColor(14); // Yellow for Name
                    cout << setw(30) << "Name: " + items[i].name;

                    setColor(10); // Green for Quantity
                    cout << setw(15) << ("Quantity: " + to_string(items[i].quantity));

                    setColor(7);
                    space();
                    print_gradient(line_str('_'), 35, 40);

                    Sleep(15);
                }

                space(2);
                set_cursor(0, 17);
                print("Command: ", -28);
                
                print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
                cout << "\033[54D";
                getline(cin, command);
                if(exit_key(command) || back_key(command)) break;

                // Handle navigation
                if (right_key(command)) {
                    if (currentPage < totalPages - 1) currentPage++;
                    continue;
                }
                else if (db_right_key(command)) {
                    currentPage = min(currentPage + 2, totalPages - 1);
                    continue;
                }
                else if (tri_right_key(command)) {
                    currentPage = totalPages - 1;
                    continue;
                }
                else if (left_key(command)) {
                    if (currentPage > 0) currentPage--;
                    continue;
                }
                else if (db_left_key(command)) {
                    currentPage = max(currentPage - 2, 0);
                    continue;
                }
                else if (tri_left_key(command)) {
                    currentPage = 0;
                    continue;
                }

                if(convert_case(command, "lower").substr(0,6) == "borrow") {
                    string idStr = command.substr(7);
                    if(isdigit(idStr[0])) {
                        int quantity;
                        set_cursor(31, 17);
                        cout << "\r";
                        print("Quantity: ", -28);
                        cout << "                  ";
                        set_cursor(17, 17);
                        cin >> quantity;

                        requestItems(stoi(idStr), quantity, name, id, date);
                        cin.ignore();
                        continue;
                    }
                }

                set_cursor(0, 17);
                print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
                Sleep(2000);
                continue;
            }
            while(true);
            continue;
        }

        else if(my_requests_key(choice)) {
            clearScreen();
            vector<RequestItem> requests;
            ifstream file("requestItem.txt");
            RequestItem req;
            bool refetch = false;

            // Read all requests into vector
            while (file >> req.reqId >> req.itemId >> req.itemName 
                   >> req.itemQuan >> req.borrowerId >> req.borrowerName >> req.date) {
                if(req.borrowerId == id) {
                    requests.push_back(req);
                }
            }
            file.close();

            const int REQUESTS_PER_PAGE = 5;
            int currentPage = 0;
            int totalPages = (requests.size() + REQUESTS_PER_PAGE - 1) / REQUESTS_PER_PAGE;
            string command;

            do {
                if(refetch){
                    requests.clear();
                    ifstream file("requestItem.txt");

                    while (file >> req.reqId >> req.itemId >> req.itemName 
                           >> req.itemQuan >> req.borrowerId >> req.borrowerName >> req.date) {
                        if(req.borrowerId == id) {
                            requests.push_back(req);
                        }
                    }
                    file.close();

                    totalPages = (requests.size() + REQUESTS_PER_PAGE - 1) / REQUESTS_PER_PAGE;
                    if(currentPage > totalPages){
                        currentPage = 0;
                    }
                    refetch = false;
                }

                clearScreen();
                cout << " <<" << string(term_width * 0.39, ' ') << " My Requests " << string(term_width * 0.37, ' ') << " >>\n";
                print_gradient(line_str('_'), 35, 40);

                // Display requests for current page
                int start = currentPage * REQUESTS_PER_PAGE;
                int end = min(start + REQUESTS_PER_PAGE, (int)requests.size());

                for (int i = start; i < end; i++) {
                    cout << "\t\t";
                    
                    cout << Color::cyan;
                    cout << left << setw(20) << ("Request ID: " + to_string(requests[i].reqId));
                    
                    cout << Color::yellow;
                    cout << setw(25) << ("Item: " + requests[i].itemName);
                    
                    cout << Color::light_magenta;
                    cout << setw(15) << ("Qty: " + to_string(requests[i].itemQuan));
                    
                    space();
                    cout << "\t";
                    
                    cout << Color::green;
                    cout << setw(20) << ("Item ID: " + to_string(requests[i].itemId));
                    
                    cout << Color::light_red;
                    cout << setw(25) << ("Date: " + requests[i].date);

                    cout << Color::reset;
                    space();
                    print_gradient(line_str('_'), 35, 40);
                    Sleep(30);
                }

                space(2);
                print("Command: ", -28);
                print(Color::gray + "Page " + to_string(currentPage + 1) + " of " + to_string(totalPages) + Color::reset, 15);
                cout << "\033[54D";
                getline(cin, command);

                if(exit_key(command) || back_key(command)) break;

                // Handle navigation
                if (right_key(command)) {
                    if (currentPage < totalPages - 1) currentPage++;
                    continue;
                }
                else if (db_right_key(command)) {
                    currentPage = min(currentPage + 2, totalPages - 1);
                    continue;
                }
                else if (tri_right_key(command)) {
                    currentPage = totalPages - 1;
                    continue;
                }
                else if (left_key(command)) {
                    if (currentPage > 0) currentPage--;
                    continue;
                }
                else if (db_left_key(command)) {
                    currentPage = max(currentPage - 2, 0);
                    continue;
                }
                else if (tri_left_key(command)) {
                    currentPage = 0;
                    continue;
                }

                if(convert_case(command, "lower").substr(0,6) == "cancel") {
                    string idStr = command.substr(7);
                    if(isdigit(idStr[0])) {
                        cancelItems(stoi(idStr));
                        refetch = true;
                        continue;
                    }
                }

                set_cursor(0, 17);
                print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
                Sleep(2000);
            } while(true);
            continue;
        }

        else if(my_borrows_key(choice)){
            readMyBorrow(id);
            continue;
        }

        else if(my_cancellations_key(choice)) {
            readMyCancelled(id);
            continue;
        }

        else if(account_settings_key(choice)) {
            do {
                clearScreen();
                
                space(4);
                line_title("Account Settings", '=', Color::light_cyan, Color::yellow);
                space(2);

                print_triple_input_box("Change Password", "Logout", "Back", 20, 3, 1, Color::light_yellow);
                space(2);
                print_line('=', Color::light_cyan);
                space(4);
                
                print_input_box(20, 0, Config::color_theme, "command", false);
                set_cursor(31, 16);
                
                string settingsChoice;
                getline(cin, settingsChoice);

                if(exit_key(settingsChoice) || back_key(settingsChoice)) break;

                if(change_password_key(settingsChoice)) {
                    clearScreen();
                    
                    space(2);
                    line_title("Change Password", '=', Color::light_cyan, Color::yellow);
                    space();
                    
                    print_input_box(20, 0, Color::white, "current password", false);
                    space(2);
                    print_input_box(20, 0, Color::white, "new password", false); 
                    space(2);
                    print_input_box(20, 0, Color::white, "confirm password", false);

                    space(2);
                    print_line('=', Color::light_cyan);
                    space();

                    set_cursor(31, 5);
                    string currentPass;
                    getline(cin, currentPass);
                    if(exit_key(currentPass) || back_key(currentPass)) continue;

                    set_cursor(31, 9);  
                    string newPass;
                    getline(cin, newPass);
                    if(exit_key(newPass) || back_key(newPass)) continue;

                    set_cursor(31, 13);
                    string confirmPass;
                    getline(cin, confirmPass);
                    if(exit_key(confirmPass) || back_key(confirmPass)) continue;

                    if(currentPass == password){
                        if(newPass == confirmPass){
                            changePass(id, confirmPass);
                            set_cursor(0, 18);
                            print("      Password Changed Successfully      ", 0, {Color::bg_light_green, Color::black});
                            Sleep(2000);
                        }
                        else{
                            set_cursor(0, 18);
                            print("      Passwords Do Not Match      ", 0, {Color::bg_light_red, Color::black});
                            Sleep(2000);
                        }
                    }
                    else{
                        set_cursor(0, 18);
                        print("      Current Password Is Incorrect      ", 0, {Color::bg_light_red, Color::black});
                        Sleep(2000);
                    }
                }
                else if(logout_key(settingsChoice)) {
                    // Logout Animation
                    clearScreen();

                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out           ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out .         ", 0, {Color::bg_white, Color::black}); 
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out . .       ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8); 
                    print_gradient(line_str(' '), 244, 255, true);
                    space(2);
                    print("         Logging out . . .     ", 0, {Color::bg_white, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 244, 255, true);
                    space(7);
                    Sleep(800);
                    
                    set_cursor(0, 8);
                    print_gradient(line_str(' '), 84, 87, true);
                    space(2);
                    print("      Successfully logged out!      ", 0, {Color::bg_bright_green, Color::black});
                    space(2);
                    print_gradient(line_str(' '), 84, 87, true);
                    space(7);
                    Sleep(3000);

                    clearScreen();
                    return;
                }
                else {
                    set_cursor(0, 17);
                    print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
                    Sleep(2000);
                }
            } while(!exit_key(choice) && !back_key(choice));

            continue;
        }

        else if(exit_key(choice) || back_key(choice)) {
            // Logout Animation
            clearScreen();

            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out           ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out .         ", 0, {Color::bg_white, Color::black}); 
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out . .       ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8); 
            print_gradient(line_str(' '), 244, 255, true);
            space(2);
            print("         Logging out . . .     ", 0, {Color::bg_white, Color::black});
            space(2);
            print_gradient(line_str(' '), 244, 255, true);
            space(7);
            Sleep(800);
            
            set_cursor(0, 8);
            print_gradient(line_str(' '), 84, 87, true);
            space(2);
            print("      Successfully logged out!      ", 0, {Color::bg_bright_green, Color::black});
            space(2);
            print_gradient(line_str(' '), 84, 87, true);
            space(7);
            Sleep(3000);

            clearScreen();
            return;
        }

        else {
            set_cursor(0, 18);
            print("      Invalid Command      ", 0, {Color::bg_light_red, Color::black});
            Sleep(2000);
            continue;
        }

    } while(!exit_key(choice) && !back_key(choice));
}


int main() {
    system("chcp 65001 > nul");
    set_terminal_size();
    
    clearScreen();

    // adminDashboard(12, "Kc-Sean", "Sean-Brix", "IT-DEPT", "admin", "121802");
	userDashboard(10 , "devacc", "devacc", "IT-Dept" , "user", "121802");
    
    string line_color = "\e[47m";
    
    string user_prompt;
    
    do{
        space(2);
        print_gradient(line_str(' '), 227, 231, true);
        print(line_title_str("SUPPLYSYNC",'='));
        print_gradient(line_str(' '), 227, 231, true);
        space(4);
        
        print("LOGIN", -24);
        print("REGISTER", -27);
        print("SETTINGS", -27);
        print("EXIT", -27);
        space(4);

        print_gradient(line_str(' '), 228, 231, true);
        print(line_str('='));
        print_gradient(line_str(' '), 228, 231, true);

        space(2);
        print_input_box(15, 0, Config::color_theme, "input", false);
        set_cursor(33, 17);
        cout.flush();
        
        cin >> user_prompt;
        user_prompt = convert_case(user_prompt, "lower");

        if(login_key(user_prompt)){
            // ENTER LOGIN
            loginUser();
            system("cls");
            cout.flush();
            continue;
        }
        else if(register_key(user_prompt)){
            // ENTER REGISTER
            registerUser();
            system("cls");
            cout.flush();
            continue;
        }
        else if(setting_key(user_prompt)){
            // ENTER SETTINGS
            open_settings();
            system("cls");
            cout.flush();
            continue;
        }
        else if(exit_key(user_prompt)){
            space(1);
            char exit_line = ' ';
            string exit_color = Color::bg_red;

            set_cursor(0, 3);
            line_title("SHUTTING DOWN", exit_line, exit_color, Config::color_theme);
            set_cursor(0, 13);
            print_line(exit_line, exit_color);
            space();
            
            set_cursor(37, 17);
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

    return 0;
}

// Split function definition 
vector<string> split(const string &s, char delimiter){ 
    vector<string> tokens; string token; 
    stringstream ss(s); 
    while (getline(ss, token, delimiter)) { 
        tokens.push_back(token); 
    } 
    return tokens;
}

// SETTINGS PAGE
void open_settings() {
    system("cls");
    cin.ignore();
    
    while(true) {
        // Display header
        space();
        print_gradient(line_str('='), 35, 40);
        space(2);
        print("SETTINGS", 0, {"\e[1;36m"});
        space(2);
        
        // Display current keybinds
        print("CURRENT KEYBINDS:", 1, {"\e[0;33m"});
        space(2);
        
        print("Exit: ", -5, {"\e[1;36m"});
        for(string key : exit_keybinds()) cout << key << " ";
        space();
        
        print("Back: ", -5, {"\e[1;36m"});
        for(string key : back_keybinds()) cout << key << " ";
        space();
        
        print("Right Page: ", -8, {"\e[1;36m"});
        for(string key : right_keybinds()) cout << key << " ";
        space();
        
        print("Left Page: ", -7, {"\e[1;36m"});
        for(string key : left_keybinds()) cout << key << " ";
        space();
        
        print("Double Right: ", -9, {"\e[1;36m"});
        for(string key : db_right_keybinds()) cout << key << " ";
        space();
        
        print("Double Left: ", -8, {"\e[1;36m"});
        for(string key : db_left_keybinds()) cout << key << " "; 
        space(2);
        
        // Display commands
        print_gradient(line_str('-'), 35, 40);
        space();
        
        space();
        print("'add'/'remove' + 'category' + 'key'", 0, {Color::gray});
        space(2);

        // Input box
        print_input_box(30, 0, Config::color_theme, "command", false);
        set_cursor(26, 18);
        
        string command;
        getline(cin, command);

        if(exit_key(command)) return;
        if(back_key(command)) return;
        
        vector<string> cmds = split(command, ' ');
        if(cmds.size() < 3) {
            set_cursor(0, 15);
            print("                  Invalid Command                  ", 0, {Color::bg_red, Color::white});
            Sleep(2000);
            system("cls");
            continue;
        }

        string action = convert_case(cmds[0], "lower");
        string category = convert_case(cmds[1], "lower"); 
        string key = cmds[2];

        if(action == "add") {
            if(category == "exit") exit_add(key);
            else if(category == "back") back_add(key);
            else if(category == "right") right_add(key);
            else if(category == "left") left_add(key);
            else if(category == "db_right") db_right_add(key);
            else if(category == "db_left") db_left_add(key);
            else {

                set_cursor(0, 15);
                print("                  Invalid category                  ", 0, {Color::bg_red, Color::white});
                Sleep(2000);
                system("cls");
                continue;
            }

            set_cursor(0, 15);
            print("               Key Added Successfully               ", 0, {Color::bg_light_blue, Color::black});
        }
        else if(action == "remove") {
            if(category == "exit") exit_remove(key);
            else if(category == "back") back_remove(key); 
            else if(category == "right") right_remove(key);
            else if(category == "left") left_remove(key);
            else if(category == "db_right") db_right_remove(key);
            else if(category == "db_left") db_left_remove(key);
            else {

                set_cursor(0, 15);
                print("                  Invalid category                  ", 0, {Color::bg_red, Color::white});
                Sleep(2000);
                system("cls");
                continue;
            }
            set_cursor(0, 15);
            print("              Key Removed Successfully              ", 0, {Color::bg_light_blue, Color::black});
        }
        
        Sleep(2000);
        system("cls");
    }
}