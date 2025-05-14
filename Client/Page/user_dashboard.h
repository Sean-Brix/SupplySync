#ifndef USER_DASHBOARD_H
#define USER_DASHBOARD_H

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
inline std::string to_lower_userdashboard(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

//? ------ MY BORROW KEYBINDS ------

inline std::vector<std::string>& my_borrow_keybinds() {
    static std::vector<std::string> keybinds = {"my borrows", "my borrow"};
    return keybinds;
}

inline bool my_borrows_key(std::string input) {
    input = to_lower_userdashboard(input);
    const auto keybinds = my_borrow_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void my_borrows_add(const std::string& key) {
    auto& keybinds = my_borrow_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_userdashboard(key));
    }
}

inline void my_borrows_remove(const std::string& key) {
    auto& keybinds = my_borrow_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)), keybinds.end());
}

//? ------ MY CANCELATION KEYBINDS ------

inline std::vector<std::string>& my_cancellations_keybinds() {
    static std::vector<std::string> keybinds = {"my cancellation", "my cancel", "my cancellation", "my cancellations"};
    return keybinds;
}

inline bool my_cancellations_key(std::string input) {
    input = to_lower_userdashboard(input);
    const auto keybinds = my_cancellations_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void my_cancellations_add(const std::string& key) {
    auto& keybinds = my_cancellations_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_userdashboard(key));
    }
}

inline void my_cancellations_remove(const std::string& key) {
    auto& keybinds = my_cancellations_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)), keybinds.end());
}

//? ------ MY REQUEST KEYBINDS ------

inline std::vector<std::string>& my_requests_keybinds() {
    static std::vector<std::string> keybinds = {"my request", "my requests"};
    return keybinds;
}

inline bool my_requests_key(std::string input) {
    input = to_lower_userdashboard(input);
    const auto keybinds = my_requests_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void my_requests_add(const std::string& key) {
    auto& keybinds = my_requests_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_userdashboard(key));
    }
}

inline void my_requests_remove(const std::string& key) {
    auto& keybinds = my_requests_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)), keybinds.end());
}


//? ------ CANCEL REQUEST KEYBINDS ------

inline std::vector<std::string>& cancel_request_keybinds() {
    static std::vector<std::string> keybinds = {"cancel request", "cancel requests"};
    return keybinds;
}

inline bool cancel_request_key(std::string input) {
    input = to_lower_userdashboard(input);
    const auto keybinds = cancel_request_keybinds();
    for(const auto& key : keybinds) {
        if(input == key) return true;
    }
    return false;
}

inline void cancel_request_add(const std::string& key) {
    auto& keybinds = cancel_request_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)) == keybinds.end()) {
        keybinds.push_back(to_lower_userdashboard(key));
    }
}

inline void cancel_request_remove(const std::string& key) {
    auto& keybinds = cancel_request_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower_userdashboard(key)), keybinds.end());
}
#endif