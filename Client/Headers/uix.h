#ifndef UIX_H
#define UIX_H

#include <string>
#include "Color.h"
#include "config.h"
using namespace std;
using namespace Color;
using namespace Config;

void set_terminal_size();
void space(const int count = 1);
void print(const string &text, const int side = 0, const vector<string> &colors = {"\e[0m"});
void print_right(const string &text, const int side = 0, const string color = "\e[0m");
void print_left(const string &text, const int side = 0, const string color = "\e[0m");
void print_sides(const string &left_text, const string &right_text, int side = 0, const string &left_color = "\e[0m", const string &right_color = "\e[0m");
void print_error(const string &text, const int side = 0);
void print_triple_text(const string &left_text, const string &middle_text, const string &right_text, 
    int side = 0, const string &left_color = Config::text_color, 
    const string &middle_color = Config::text_color, 
    const string &right_color = Config::text_color
);

void print_line(const char symbol = '_', const string &color = "\e[1;30m");
void print_gradient(const string &text, const int &color_start = 32, const int &color_end = 45, bool background = false, const int side = 0);
void line_title(const string text, const char symbol, const string line_color, const string text_color);

void set_cursor(int x, int y);
void move_cursor(int dx, int dy);
void clear_line(int line_number);

void print_input_box(int width, const int side = 0, const string &bg_color = "\033[48;5;7m");
void print_input_box(int width, const int side, const string &bg_color, const string &label, bool side_label, const string &position = "left", bool inside_label = false);
void print_triple_input_box(
    const string &label1, const string &label2, const string &label3,
    int width = 18, const int cellgap = 5, const int side = 0, const string &line_color = Color::white, 
    const string &text_color = Config::text_color, const string &bg_color = Config::color_theme
);
void print_label_box(
    const string &label,
    int width = 18, const int side = 0, const string &line_color = Color::white, 
    const string &text_color = Config::text_color, const string &bg_color = Config::color_theme
);

string line_title_str(const string text, const char symbol);
string centered_str(const string &text, const int side = 0);
string line_str(const char symbol = '-');
string line_str(const string& pattern = "─");
string convert_case(const string &subject, const string &option = "");

extern int term_width;
extern int term_height;

#endif