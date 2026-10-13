#ifndef CSTAR_INTERACTIVE_H
#define CSTAR_INTERACTIVE_H

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

class Interactive
{
    static constexpr char ESC =  '\033';
    static constexpr char BSP =  '\010';
    static constexpr char DEL =  '\177';
    static constexpr char LBK =  '[';
    static constexpr char CUU = 'A';
    static constexpr char CUD = 'B';
    static constexpr char CUF = 'C';
    static constexpr char CUB = 'D';
    static constexpr char CLR = 'K';

    static inline Interactive *singleton = nullptr;

#ifdef MAC
    termios sav = {0};
    bool tio_sv = false;
#endif

public:
    static Interactive *getInstance();
    Interactive();
    ~Interactive();

    Interactive(const Interactive&) = delete;
    Interactive& operator=(const Interactive&) = delete;

    // Delete move constructor and move assignment operator
    Interactive(Interactive&&) = delete;
    Interactive& operator=(Interactive&&) = delete;

    int read_char();
    void move_cursor(int dx, int dy);
    void clear_line(int dir);
    void redraw_line(const std::string& line, int cursor_pos);

    std::string getCommand();

private:
    std::vector<std::string> history;
    int history_index = 0;
};
#endif //CSTAR_INTERACTIVE_H