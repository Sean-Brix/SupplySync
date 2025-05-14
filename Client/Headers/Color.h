// ANSIColors.h
#ifndef COLOR_H
#define COLOR_H

#include <string>
using namespace std;

namespace Color {

    // Foreground colors
    const string black = "\033[38;5;0m";
    const string red = "\033[38;5;1m";
    const string green = "\033[38;5;2m";
    const string yellow = "\033[38;5;3m";
    const string blue = "\033[38;5;4m";
    const string magenta = "\033[38;5;5m";
    const string cyan = "\033[38;5;6m";
    const string white = "\033[38;5;7m";

    // Background colors
    const string bg_black = "\033[48;5;0m";
    const string bg_red = "\033[48;5;1m";
    const string bg_green = "\033[48;5;2m";
    const string bg_yellow = "\033[48;5;3m";
    const string bg_blue = "\033[48;5;4m";
    const string bg_magenta = "\033[48;5;5m";
    const string bg_cyan = "\033[48;5;6m";
    const string bg_white = "\033[48;5;7m";
    
    const std::string reset = "\033[0m";          // Reset all attributes
    const std::string bold = "\033[1m";           // Bold text
    const std::string italic = "\033[3m";         // Italic text
    const std::string underline = "\033[4m";      // Underline text
    const std::string strikethrough = "\033[9m";   // Strikethrough text

    // High color codes (256 colors)
    const string gray = "\033[38;5;8m";
    const string light_red = "\033[38;5;9m";
    const string light_green = "\033[38;5;10m";
    const string light_yellow = "\033[38;5;11m";
    const string light_blue = "\033[38;5;12m";
    const string light_magenta = "\033[38;5;13m";
    const string light_cyan = "\033[38;5;14m";
    const string light_white = "\033[38;5;15m";

    // Bright colors (Foreground)
    const string bright_black = "\033[38;5;16m";
    const string bright_red = "\033[38;5;196m";
    const string bright_green = "\033[38;5;46m";
    const string bright_yellow = "\033[38;5;226m";
    const string bright_blue = "\033[38;5;33m";
    const string bright_magenta = "\033[38;5;201m";
    const string bright_cyan = "\033[38;5;51m";
    const string bright_white = "\033[38;5;15m";

    // High color codes (Background)
    const string bg_gray = "\033[48;5;8m";
    const string bg_light_red = "\033[48;5;9m";
    const string bg_light_green = "\033[48;5;10m";
    const string bg_light_yellow = "\033[48;5;11m";
    const string bg_light_blue = "\033[48;5;12m";
    const string bg_light_magenta = "\033[48;5;13m";
    const string bg_light_cyan = "\033[48;5;14m";
    const string bg_light_white = "\033[48;5;15m";

    // Bright background colors
    const string bg_bright_black = "\033[48;5;16m";
    const string bg_bright_red = "\033[48;5;196m";
    const string bg_bright_green = "\033[48;5;46m";
    const string bg_bright_yellow = "\033[48;5;226m";
    const string bg_bright_blue = "\033[48;5;33m";
    const string bg_bright_magenta = "\033[48;5;201m";
    const string bg_bright_cyan = "\033[48;5;51m";
    const string bg_bright_white = "\033[48;5;15m";
}

#endif
