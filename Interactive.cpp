#include "Interactive.h"
Interactive *Interactive::singleton = nullptr;
Interactive *Interactive::getInstance()
{
    if (nullptr == singleton)
    {
        singleton = new Interactive();
    }
    return singleton;
}
#ifdef _WIN32
Interactive::Interactive() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
Interactive::~Interactive() {
    std::cout << "\r\n" << std::flush;
}
#else
Interactive::Interactive()
{
    termios raw;
    ::tcgetattr(STDIN_FILENO, &raw);
    sav = raw;
    tio_sv = true;
    ::cfmakeraw(&raw);
    ::tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}
Interactive::~Interactive()
{
    std::cout << "\r\n" << std::flush;
    ::tcsetattr(STDIN_FILENO, TCSANOW, &sav);
    tio_sv = false;
}
#endif

int Interactive::read_char() {
#ifdef _WIN32
    return _getch(); // Returning the raw integer so that 224 doesn't overflow
#else
    int c = 0;
    ::read(STDIN_FILENO, &c, 1);
    return c;
#endif
}
void Interactive::move_cursor(int dx, int dy) {
    std::string dst;
    char cmd;
    if (dx != 0)
    {
        cmd = (dx > 0) ? CUF : (dx = -dx, CUB);
        dst = std::to_string(dx);
        std::cout << ESC << LBK << dst << cmd << std::flush;
    }
    if (dy != 0)
    {
        cmd = (dy > 0) ? CUD : (dy = -dy, CUU);
        dst = std::to_string(dy);
        std::cout << ESC << LBK << dst << cmd << std::flush;
    }
}
void Interactive::clear_line(int dir) {
    char cmd;
    if (dir == 0)
        cmd = '2';  // clear full line
    else if (dir > 0)
        cmd = '0';  // clear cursor to end
    else
        cmd = '1';  // clear cursor to beginning
    std::cout << ESC << LBK << cmd << CLR << std::flush;
}
void Interactive::redraw_line(const std::string& line, int cursor_pos) {
    std::cout << "\r* " << line; // Return to start of line and print prompt + string
    clear_line(1);               // Clear any leftover characters from cursor to end of terminal line

    int spaces_back = line.length() - cursor_pos;
    if (spaces_back > 0) {
        move_cursor(-spaces_back, 0);
    }
}
std::string Interactive::getCommand() {
    std::string current_line = "";
    int cursor_pos = 0;

    // Always start at the end of the history when typing a new command
    history_index = history.size();

    // Replaced the "Sandbox Started" message with a standard prompt
    redraw_line(current_line, cursor_pos);

    while (true) {
        int ch = read_char();

        // 1. Enter Key Submission
        if (ch == '\r' || ch == '\n') {
            std::cout << "\r\n"; // Move terminal cursor down visually

            // Save to history if it's not blank
            if (!current_line.empty()) {
                history.push_back(current_line);
            }

            // Return the string back to the Cstar interpreter!
            return current_line;
        }

        // 2. Backspace
        else if (ch == BSP || ch == DEL) {
            if (cursor_pos > 0) {
                current_line.erase(cursor_pos - 1, 1);
                cursor_pos--;
                redraw_line(current_line, cursor_pos);
            }
        }

        // 3. Mac/Linux Arrow Keys
        else if (ch == ESC) {
            if (read_char() == LBK) {
                int arrow = read_char();
                if (arrow == CUF && cursor_pos < current_line.length()) cursor_pos++;
                else if (arrow == CUB && cursor_pos > 0) cursor_pos--;
                else if (arrow == CUU && history_index > 0) {
                    history_index--;
                    current_line = history[history_index];
                    cursor_pos = current_line.length();
                }
                else if (arrow == CUD && history_index < history.size()) {
                    history_index++;
                    current_line = (history_index == history.size()) ? "" : history[history_index];
                    cursor_pos = current_line.length();
                }
                redraw_line(current_line, cursor_pos);
            }
        }

        // 4. Windows Arrow Keys
        else if (ch == 224 || ch == 0 || ch == -32) {
            int arrow = read_char();
            if (arrow == 77 && cursor_pos < current_line.length()) cursor_pos++;
            else if (arrow == 75 && cursor_pos > 0) cursor_pos--;
            else if (arrow == 72 && history_index > 0) {
                history_index--;
                current_line = history[history_index];
                cursor_pos = current_line.length();
            }
            else if (arrow == 80 && history_index < history.size()) {
                history_index++;
                current_line = (history_index == history.size()) ? "" : history[history_index];
                cursor_pos = current_line.length();
            }
            redraw_line(current_line, cursor_pos);
        }

        // 5. Standard Typing
        else if (ch >= 32 && ch <= 126) {
            current_line.insert(cursor_pos, 1, static_cast<char>(ch));
            cursor_pos++;
            redraw_line(current_line, cursor_pos);
        }
    }
}
