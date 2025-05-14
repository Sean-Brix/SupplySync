#ifndef KEYBINDS_H
#define KEYBINDS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <fstream>

// Helper function to convert string to lowercase
inline std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

// LOGIN KEYBINDS
inline std::vector<std::string>& login_keybinds() {
    static std::vector<std::string> keybinds = {"login", "l", "log"};
    return keybinds;
}

inline bool login_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = login_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// REGISTER KEYBINDS
inline std::vector<std::string>& register_keybinds() {
    static std::vector<std::string> keybinds = {"reg", "r", "register"};
    return keybinds;
}

inline bool register_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = register_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// SETTING KEYBINDS
inline std::vector<std::string>& setting_keybinds() {
    static std::vector<std::string> keybinds = {"s", "set", "settings"};
    return keybinds;
}

inline bool setting_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = setting_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// BACK KEYBINDS
inline std::vector<std::string>& back_keybinds() {
    static std::vector<std::string> keybinds = {"b", "back", "z", "0"};
    return keybinds;
}

inline bool back_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = back_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// EXIT KEYBINDS
inline std::vector<std::string>& exit_keybinds() {
    static std::vector<std::string> keybinds = {"exit", "x", "quit", "q", "e"};
    return keybinds;
}

inline bool exit_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = exit_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// LEFT KEYBINDS
inline std::vector<std::string>& left_keybinds() {
    static std::vector<std::string> keybinds = {"<", "{", "a", "4"};
    return keybinds;
}

inline bool left_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = left_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// DOUBLE LEFT KEYBINDS
inline std::vector<std::string>& db_left_keybinds() {
    static std::vector<std::string> keybinds = {"<<", "{{", "aa", "44"};
    return keybinds;
}

inline bool db_left_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = db_left_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}


// RIGHT KEYBINDS
inline std::vector<std::string>& right_keybinds() {
    static std::vector<std::string> keybinds = {">", "}", "d", "6"};
    return keybinds;
}

inline bool right_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = right_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// DOUBLE RIGHT KEYBINDS
inline std::vector<std::string>& db_right_keybinds() {
    static std::vector<std::string> keybinds = {">>", "}}", "dd", "66"};
    return keybinds;
}

inline bool db_right_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = db_right_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// TRIPLE LEFT KEYBINDS
inline std::vector<std::string>& tri_left_keybinds() {
    static std::vector<std::string> keybinds = {"<<<", "{{{", "aaa", "444"};
    return keybinds;
}
inline bool tri_left_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = tri_left_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}

// TRIPLE RIGHT KEYBINDS
inline std::vector<std::string>& tri_right_keybinds() {
    static std::vector<std::string> keybinds = {">>>", "}}}", "ddD", "666"};
    return keybinds;
}

inline bool tri_right_key(std::string input) {
    input = to_lower(input);
    const auto keybinds = tri_right_keybinds();
    
    for(const auto& key : keybinds) {
        if(input == key) {
            return true;
        }
    }
    return false;
}



//?  ---------------- KEYBINDS MANAGEMENT ----------------

// Login keybinds management
inline void login_add(const std::string& key) {
    auto& keybinds = login_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void login_remove(const std::string& key) {
    auto& keybinds = login_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Register keybinds management
inline void register_add(const std::string& key) {
    auto& keybinds = register_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void register_remove(const std::string& key) {
    auto& keybinds = register_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Settings keybinds management
inline void setting_add(const std::string& key) {
    auto& keybinds = setting_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void setting_remove(const std::string& key) {
    auto& keybinds = setting_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Back keybinds management
inline void back_add(const std::string& key) {
    auto& keybinds = back_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void back_remove(const std::string& key) {
    auto& keybinds = back_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Exit keybinds management
inline void exit_add(const std::string& key) {
    auto& keybinds = exit_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void exit_remove(const std::string& key) {
    auto& keybinds = exit_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Left keybinds management
inline void left_add(const std::string& key) {
    auto& keybinds = left_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void left_remove(const std::string& key) {
    auto& keybinds = left_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Double Left keybinds management
inline void db_left_add(const std::string& key) {
    auto& keybinds = db_left_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void db_left_remove(const std::string& key) {
    auto& keybinds = db_left_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

//  Triple Left keybinds management
inline void tri_left_add(const std::string& key) {
    auto& keybinds = tri_left_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void tri_left_remove(const std::string& key) {
    auto& keybinds = tri_left_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Right keybinds management
inline void right_add(const std::string& key) {
    auto& keybinds = right_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void right_remove(const std::string& key) {
    auto& keybinds = right_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Double Right keybinds management
inline void db_right_add(const std::string& key) {
    auto& keybinds = db_right_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void db_right_remove(const std::string& key) {
    auto& keybinds = db_right_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}

// Triple Right keybinds management
inline void tri_right_add(const std::string& key) {
    auto& keybinds = tri_right_keybinds();
    if(std::find(keybinds.begin(), keybinds.end(), to_lower(key)) == keybinds.end()) {
        keybinds.push_back(to_lower(key));
    }
}

inline void tri_right_remove(const std::string& key) {
    auto& keybinds = tri_right_keybinds();
    keybinds.erase(std::remove(keybinds.begin(), keybinds.end(), to_lower(key)), keybinds.end());
}



#endif
