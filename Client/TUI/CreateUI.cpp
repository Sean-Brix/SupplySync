// IMPORTS
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <cctype>
#include <algorithm>
#include <limits>
#include <regex>
#include <cmath>
#include "uix.h"
#include "../Headers/Color.h"

// NAMESPACES
using namespace std;
using namespace Color;

// GLOBAL VARIABLE
int term_width = 80; 
int term_height = 20;

//? ________________________________ FUNCTION  ________________________________ 

// Line with Text
void line_title(const string text, const char symbol, const string line_color, const string text_color){
    string decorated_text = "  " + text + "  ";  // Text with padding
    int text_length = decorated_text.length();
    int line_length = term_width;

    // Calculate how many symbols go on each side
    int remaining = line_length - text_length;
    if (remaining < 0) remaining = 0;

    int left_len = remaining / 2;
    int right_len = remaining - left_len;

    // Create the left and right parts of the line
    string left = string(left_len, symbol);
    string right = string(right_len, symbol);

    // Combine and print with colors
    cout << line_color << left << text_color << decorated_text << line_color << right << "\033[0m" << endl;
}

// ADDS ENDLINE
void space(const int count){
    for(int i = 0; i < count; i++){
        cout << "\n";
    }
}

// TERMINAL SIZE
void set_terminal_size(){

    ostringstream console;
    console << "mode con: cols=" << term_width << " lines=" <<term_height;
    string command = console.str();

    system(command.c_str());

    return;
}

// CENTER ALL TEXT
void print(const string &text, const int side, const vector<string> &colors){ 
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) + side;
    cout << string(spaces, ' ');
    
    // Apply all colors
    for (const string &color : colors) {
        cout << color;
    }
    cout << fulltext << "\e[0m";
}

// PRINT TO RIGHT
void print_right(const string &text, const int side, const string color) {
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext) { 
        if (ch == '\n' || ch == '\t') continue; 
        effective_length += 1; 
    } 

    // Quarter-width centering (right side)
    int quarter_width = term_width / 2;
    int spaces = ((quarter_width - effective_length) / 2) + side + quarter_width;

    cout << string(max(0, spaces), ' ') << color << fulltext << (color.empty() ? "" : "\033[0m");
}

// PRINT TO LEFT
void print_left(const string &text, const int side, const string color) {
    // Move cursor up 1 line and to column 1 (start of line)
    cout << "\033[1A\r" << flush;

    // Calculate effective text length (skip \n, \t)
    int effective_length = 0;
    for (char ch : text) {
        if (ch != '\n' && ch != '\t') effective_length++;
    }

    int half_width = term_width / 2;
    int spaces = ((half_width - effective_length) / 2) + side;

    // Pad right side to clear leftovers in left half
    int total_fill = half_width;

    string output = string(max(0, spaces), ' ') + color + text + (color.empty() ? "" : "\033[0m");
    int fill = max(0, (int)total_fill - (int)output.length());
    output += string(fill, ' ');

    cout << output << flush;
}


void print_sides(const string &left_text, const string &right_text, int side, const string &left_color, const string &right_color) {

    int half_width = term_width / 2;

    // LEFT SIDE
    int left_spaces = (half_width / 2) + side;
    string left_output = string(max(0, left_spaces), ' ') + left_color + left_text + (left_color.empty() ? "" : "\033[0m");

    // RIGHT SIDE
    int right_spaces = (half_width / 2) + side;
    string right_output = string(max(0, right_spaces), ' ') + right_color + right_text + (right_color.empty() ? "" : "\033[0m");

    // Move cursor up and return to start to overwrite same line
    cout << "\033[1A\r" << flush;

    // Combine and print
    cout << left_output;

    // Pad if needed to reach middle of screen before right text
    int pad_to_middle = max(0, term_width / 2 - (int)left_output.length());
    cout << string(pad_to_middle, ' ');

    cout << right_output << endl;
}

void print_triple_text(const string &left_text, const string &middle_text, const string &right_text, 
    int side, const string &left_color, const string &middle_color, const string &right_color) 
{
    int section_width = term_width / 3;  // Split terminal into thirds

    // Calculate effective lengths
    int left_len = left_text.length();
    int middle_len = middle_text.length();
    int right_len = right_text.length();

    // Calculate padding
    int left_padding = (section_width - left_len) / 2;
    int middle_padding = (section_width - middle_len) / 2;
    int right_padding = (section_width - right_len) / 2;

    // Print initial side padding
    for (int i = 0; i < side; i++) cout << ' ';

    // Print left section
    for (int i = 0; i < left_padding; i++) cout << ' ';
    cout << left_color << left_text << "\033[0m";
    for (int i = 0; i < section_width - left_len - left_padding; i++) cout << ' ';

    // Print middle section
    for (int i = 0; i < middle_padding; i++) cout << ' ';
    cout << middle_color << middle_text << "\033[0m";
    for (int i = 0; i < section_width - middle_len - middle_padding; i++) cout << ' ';

    // Print right section
    for (int i = 0; i < right_padding; i++) cout << ' ';
    cout << right_color << right_text << "\033[0m";
    for (int i = 0; i < section_width - right_len - right_padding; i++) cout << ' ';
    cout << endl;
}



// ERROR PANEL
void print_error(const string &text, const int side){
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) + side; 
    cout << string(spaces, ' ') << "\x1B[31m" << fulltext << "\e[0m";
}

// ADD A LINE TO THE TERMINAL
void print_line(const char symbol, const string &color){
    cout << color << string(term_width, symbol) << Color::reset;
}
// Line with Text (returns string)
string line_title_str(const string text, const char symbol){
    string decorated_text = "  " + text + "  ";  // Text with padding
    int text_length = decorated_text.length();
    int line_length = term_width;

    // Calculate how many symbols go on each side
    int remaining = line_length - text_length;
    if (remaining < 0) remaining = 0;

    int left_len = remaining / 2;
    int right_len = remaining - left_len;

    // Create the left and right parts of the line
    string left = string(left_len, symbol);
    string right = string(right_len, symbol);

    // Combine and return
    return left + decorated_text + right;
}

// ADD A GRADIENT TEXT
void print_gradient(const string &text, const int &color_start, const int &color_end, bool background, const int side) {
    int color_range = color_end - color_start;
    int text_length = text.length();

    // Calculate the effective length (ignore escape codes for centering)
    int effective_length = 0;
    for (char ch : text) {
        if (ch == '\n' || ch == '\t') {
            continue;
        }
        effective_length += 1;
    }

    // Calculate the spaces to center the text
    int spaces = ((term_width - effective_length) / 2) + side;
    
    // Print leading spaces
    cout << string(spaces, ' ');

    // Print the gradient text with colors
    for (int i = 0; i < text_length; ++i) {
        int color_code = color_start + (color_range * i / text_length);
        if (background) {
            cout << "\033[48;5;" << color_code << "m\033[38;5;" << color_code << "m" << text[i];
        } else {
            cout << "\033[38;5;" << color_code << "m" << text[i];
        }
    }
    
    // Reset color at the end
    cout << "\033[0m"; 
}


// RETURN A CENTERED STRING
string centered_str(const string &text, const int side){ 
    string fulltext = text;

    int effective_length = 0; 
    for (char ch : fulltext){ 
        if (ch == '\n' || ch == '\t'){ 
            continue; 
        } 
        effective_length += 1; 
    } 

    int spaces = ((term_width - effective_length) / 2) + side; 
    return string(spaces, ' ') + fulltext;
}

// RETURN A LINE STRING FOR MODIFICATION
string line_str(const char symbol){
    return string(term_width, symbol);
}

// Overloaded version that takes a string
string line_str(const string& pattern){
    string result;
    while (result.length() < static_cast<size_t>(term_width)) {
        result += pattern;
    }
    // Trim to exact width if pattern repetition went over
    return result.substr(0, term_width);
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

// Set cursor position in terminal
void set_cursor(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Get current cursor position
COORD get_cursor() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

// Move cursor relative to current position
void move_cursor(int dx, int dy) {
    COORD pos = get_cursor();
    set_cursor(pos.X + dx, pos.Y + dy);
}

// Original function
void print_input_box(int width, const int side, const string &bg_color) {
    int spaces = ((term_width - width - 2) / 2) + side;  // -2 for the edge characters
    
    // Top border
    cout << string(spaces, ' ') << "┌";
    for(int i = 0; i < width; i++) {
        cout << "─";
    } 
    cout << "┐";

    // Middle part with background color
    space(1);
    cout << string(spaces, ' ') << "ǀ" << bg_color << string(width, ' ') << "\033[0m" << "ǀ";

    // Bottom border
    space(1);
    cout << string(spaces, ' ') << "└";
    for(int i = 0; i < width; i++) {
        cout << "─";
    } 
    cout << "┘";
}

// Overloaded function with label and side positioning
void print_input_box(int width, const int side, const string &bg_color, const string &label, bool side_label, const string &position, bool inside_label) {
    int spaces = ((term_width - width - 2) / 2) + side;
    
    if (inside_label) {
        // Inside label version
        cout << string(spaces, ' ') << "┌";
        for(int i = 0; i < width; i++) cout << "─";
        cout << "┐";
        
        space(1);
        cout << string(spaces, ' ') << "ǀ";
        if (position == "left") {
            cout << bg_color << label << string(width - label.length(), ' ') << "\033[0m";
        } else if (position == "right") {
            cout << bg_color << string(width - label.length(), ' ') << label << "\033[0m";
        } else { // center
            int pad = (width - label.length()) / 2;
            cout << bg_color << string(pad, ' ') << label << string(width - pad - label.length(), ' ') << "\033[0m";
        }
        cout << "ǀ";
        
        space(1);
        cout << string(spaces, ' ') << "└";
        for(int i = 0; i < width; i++) cout << "─";
        cout << "┘";
    }
    else if (side_label) {
        // Side label version
        cout << string(spaces, ' ') << "┌";
        for(int i = 0; i < width; i++) cout << "─";
        cout << "┐";
        
        space(1);
        if (position == "left") {
            cout << string(spaces - label.length() - 1, ' ') << label << " ǀ";
        } else {
            cout << string(spaces, ' ') << "ǀ";
        }
        cout << bg_color << string(width, ' ') << "\033[0m";
        if (position == "right") {
            cout << "ǀ " << label;
        } else {
            cout << "ǀ";
        }
        
        space(1);
        cout << string(spaces, ' ') << "└";
        for(int i = 0; i < width; i++) cout << "─";
        cout << "┘";
    } else {
        // Top label version
        if (position == "left") {
            cout << string(spaces, ' ') << "┌─ " << label << " ";
            int remaining = width - label.length() - 3;
            for(int i = 0; i < remaining; i++) cout << "─";
            cout << "┐";
        } else {
            cout << string(spaces, ' ') << "┌";
            int remaining = width - label.length() - 3;
            for(int i = 0; i < remaining; i++) cout << "─";
            cout << " " << label << " ─┐";
        }
        
        space(1);
        cout << string(spaces, ' ') << "ǀ" 
             << bg_color << string(width, ' ') << "\033[0m" << "ǀ";
        
        space(1);
        cout << string(spaces, ' ') << "└";
        for(int i = 0; i < width; i++) cout << "─";
        cout << "┘";
    }
}


// Clear a specific line in terminal
void clear_line(int line_number) {
    COORD originalPos = get_cursor();
    set_cursor(0, line_number);
    cout << string(term_width, ' ');
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), originalPos);
}

void print_triple_input_box(
    const string &label1, const string &label2, const string &label3,
    int width, const int cellgap, const int side, const string &line_color, 
    const string &text_color, const string &bg_color  
){
    // Calculate actual widths needed for each box
    int width1 = max(width, (int)label1.length() + 2);
    int width2 = max(width, (int)label2.length() + 2);
    int width3 = max(width, (int)label3.length() + 2);
    
    int spaces = max(0, side + ((term_width - (width1 + width2 + width3 + 2 * cellgap)) / 4));
    
    // Top borders
    cout << string(spaces, ' ') << line_color;
    cout << "┌"; for(int i = 0; i < width1; i++) cout << "─"; cout << "┐";
    cout << string(cellgap, ' ');
    cout << "┌"; for(int i = 0; i < width2; i++) cout << "─"; cout << "┐";
    cout << string(cellgap, ' ');
    cout << "┌"; for(int i = 0; i < width3; i++) cout << "─"; cout << "┐\033[0m";

    // Labels
    space(1);
    cout << string(spaces, ' ') << line_color;
    cout << "ǀ" << bg_color << text_color << string((width1 - label1.length()) / 2, ' ') << label1 << string((width1 - label1.length() + 1) / 2, ' ') << line_color << "ǀ";
    cout << string(cellgap, ' ');
    cout << "ǀ" << bg_color << text_color << string((width2 - label2.length()) / 2, ' ') << label2 << string((width2 - label2.length() + 1) / 2, ' ') << line_color << "ǀ";
    cout << string(cellgap, ' ');
    cout << "ǀ" << bg_color << text_color << string((width3 - label3.length()) / 2, ' ') << label3 << string((width3 - label3.length() + 1) / 2, ' ') << line_color << "ǀ\033[0m";

    // Bottom borders
    space(1);
    cout << string(spaces, ' ') << line_color;
    cout << "└"; for(int i = 0; i < width1; i++) cout << "─"; cout << "┘";
    cout << string(cellgap, ' ');
    cout << "└"; for(int i = 0; i < width2; i++) cout << "─"; cout << "┘";
    cout << string(cellgap, ' ');
    cout << "└"; for(int i = 0; i < width3; i++) cout << "─"; cout << "┘\033[0m";
}

void print_label_box(
    const string &label,
    int width, const int side, const string &line_color, 
    const string &text_color, const string &bg_color
){
    // Calculate actual width needed for box
    int width_actual = max(width, (int)label.length() + 2);
    
    int spaces = max(0, side + ((term_width - width_actual) / 2));
    
    // Top border
    cout << string(spaces, ' ') << line_color;
    cout << "┌"; 
    for(int i = 0; i < width_actual; i++) cout << "─"; 
    cout << "┐\033[0m";

    // Label
    space(1);
    cout << string(spaces, ' ') << line_color;
    cout << "ǀ" << bg_color << text_color 
         << string((width_actual - label.length()) / 2, ' ') 
         << label 
         << string((width_actual - label.length() + 1) / 2, ' ') 
         << line_color << "\033[0m" << line_color << "ǀ" << Color::reset;

    // Bottom border
    space(1);
    cout << string(spaces, ' ') << line_color;
    cout << "└";
    for(int i = 0; i < width_actual; i++) cout << "─";
    cout << "┘\033[0m";
}