#ifndef ADMIN_DASHBOARD_H
#define ADMIN_DASHBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <fstream>

#include "Color.h"
#include "config.h"
using namespace std;
using namespace Color;
using namespace Config;

// Helper function to convert string to lowercase
inline std::string to_lower_dashboard(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}


//? ------ SHOW ITEMS KEYBINDS ------ 

inline std::vector<std::string>& show_items_keybinds() {
    static std::vector<std::string> keybinds = {"show items", "show item"};
    return keybinds;
}

inline bool show_items_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = show_items_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void show_items_add(const std::string& key) {
    auto& keybinds = show_items_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void show_items_remove(const std::string& key) {
    auto& keybinds = show_items_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ SHOW USERS KEYBINDS ------

inline std::vector<std::string>& show_users_keybinds() {
    static std::vector<std::string> keybinds = {"show users"};
    return keybinds;
}

inline bool show_users_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = show_users_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void show_users_add(const std::string& key) {
    auto& keybinds = show_users_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void show_users_remove(const std::string& key) {
    auto& keybinds = show_users_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ ADD ITEMS KEYBINDS ------

inline std::vector<std::string>& add_item_keybinds() {
    static std::vector<std::string> keybinds = {"add items", "add item"};
    return keybinds;
}

inline bool add_item_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = add_item_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void add_item_add(const std::string& key) {
    auto& keybinds = add_item_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void add_item_remove(const std::string& key) {
    auto& keybinds = add_item_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ BORROW REQUEST KEYBINDS ------

inline std::vector<std::string>& borrow_request_keybinds() {
    static std::vector<std::string> keybinds = {"borrow request"};
    return keybinds;
}

inline bool borrow_request_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = borrow_request_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void borrow_request_add(const std::string& key) {
    auto& keybinds = borrow_request_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void borrow_request_remove(const std::string& key) {
    auto& keybinds = borrow_request_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ BORROWED ITEMS KEYBINDS ------

inline std::vector<std::string>& borrowed_items_keybinds() {
    static std::vector<std::string> keybinds = {"borrowed items"};
    return keybinds;
}

inline bool borrowed_items_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = borrowed_items_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void borrowed_items_add(const std::string& key) {
    auto& keybinds = borrowed_items_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void borrowed_items_remove(const std::string& key) {
    auto& keybinds = borrowed_items_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ RETURNED ITEMS KEYBINDS ------

inline std::vector<std::string>& returned_items_keybinds() {
    static std::vector<std::string> keybinds = {"returned items"};
    return keybinds;
}

inline bool returned_items_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = returned_items_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void returned_items_add(const std::string& key) {
    auto& keybinds = returned_items_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void returned_items_remove(const std::string& key) {
    auto& keybinds = returned_items_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ DELETE ITEMS KEYBINDS ------

inline std::vector<std::string>& delete_items_keybinds() {
    static std::vector<std::string> keybinds = {"delete item", "delete item"};
    return keybinds;
}

inline bool delete_items_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = delete_items_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void delete_items_add(const std::string& key) {
    auto& keybinds = delete_items_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void delete_items_remove(const std::string& key) {
    auto& keybinds = delete_items_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ DELETE USER KEYBINDS ------

inline std::vector<std::string>& delete_user_keybinds() {
    static std::vector<std::string> keybinds = {"delete user"};
    return keybinds;
}

inline bool delete_user_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = delete_user_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void delete_user_add(const std::string& key) {
    auto& keybinds = delete_user_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void delete_user_remove(const std::string& key) {
    auto& keybinds = delete_user_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ ACCOUNT SETTINGS KEYBINDS ------

inline std::vector<std::string>& account_settings_keybinds() {
    static std::vector<std::string> keybinds = {"account settings"};
    return keybinds;
}

inline bool account_settings_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = account_settings_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void account_settings_add(const std::string& key) {
    auto& keybinds = account_settings_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void account_settings_remove(const std::string& key) {
    auto& keybinds = account_settings_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ LOGOUT KEYBINDS ------

inline std::vector<std::string>& logout_keybinds() {
    static std::vector<std::string> keybinds = {"logout", "sign out"};
    return keybinds;
}

inline bool logout_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = logout_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void logout_add(const std::string& key) {
    auto& keybinds = logout_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void logout_remove(const std::string& key) {
    auto& keybinds = logout_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


//? ------ CHANGE PASSWORD KEYBINDS ------

inline std::vector<std::string>& change_password_keybinds() {
    static std::vector<std::string> keybinds = {"change password", "update password"};
    return keybinds;
}

inline bool change_password_key(std::string input) {
    input = to_lower_dashboard(input);
    const auto keybinds = change_password_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void change_password_add(const std::string& key) {
    auto& keybinds = change_password_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_dashboard(key));
    }
}

inline void change_password_remove(const std::string& key) {
    auto& keybinds = change_password_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_dashboard(key)), keybinds.end());
}


#endif
