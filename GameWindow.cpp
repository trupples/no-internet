#include "GameWindow.h"

#include <Windows.h>
#include <iostream>

GameWindow::GameWindow()
    : bitmap { { Color::Cyan } }
    , text_color { { Color::Black } }
    , text { { 0 } }
{
    HANDLE stdout_console = GetStdHandle(STD_OUTPUT_HANDLE),
           stdin_console = GetStdHandle(STD_INPUT_HANDLE);
    DWORD stdout_mode, stdin_mode;

    // Input and output UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Enable output buffering (prevents flicker); enable output sequences
    std::cout.rdbuf()->pubsetbuf(0, 65536);
    GetConsoleMode(stdout_console, &stdout_mode);
    stdout_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // ANSI sequence output
    SetConsoleMode(stdout_console, stdout_mode);

    // Disable input buffering; enable input sequences
    std::cin.rdbuf()->pubsetbuf(0, 0);
    std::cin.setf(std::ios::binary);
    GetConsoleMode(stdin_console, &stdin_mode);
    stdin_mode |= ENABLE_VIRTUAL_TERMINAL_INPUT; // arrow key input as escape sequences
    stdin_mode &= ~ENABLE_LINE_INPUT; // "raw mode"
    SetConsoleMode(stdin_console, stdin_mode);

    std::cout << "\033[?1049h"; // Switch to alternate buffer
    std::cout << "\033[?25l"; // Hide cursor
    set_title("No internet");
}

GameWindow::~GameWindow()
{
    std::cout << "\033[?25h"; // Show cursor
    std::cout << "\033[?1049l"; // Switch to main buffer
}

void GameWindow::begin_frame()
{
    // Clear the buffers
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            bitmap[i * 2][j] = Color::Cyan;
            bitmap[i * 2 + 1][j] = Color::Cyan;
            collision_check_bitmap[i * 2][j] = false;
            collision_check_bitmap[i * 2 + 1][j] = false;
            text_color[i][j] = Color::Black;
            text[i][j] = 0;
        }
    }
}

void GameWindow::display_frame()
{
    std::string buf;    // Employ buffering so as to prevent flickering
    buf += "\033[1;1H"; // Goto 1, 1
    buf += "\033[2J";   // Clear display

    // Remember the previously set color so we don't fill the output buffer with kilobytes of
    // redundant escape sequences
    Color last_bg = Color::Transparent,
          last_fg = Color::Transparent;
    auto bg = [&](Color col) {if (last_bg != col) buf += color_esc_bg(col); last_bg = col; };
    auto fg = [&](Color col) {if (last_fg != col) buf += color_esc_fg(col); last_fg = col; };

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            Color top_half = bitmap[i * 2][j], bottom_half = bitmap[i * 2 + 1][j];
            char txt = text[i][j];
            if (txt >= ' ') {
                fg(text_color[i][j]);
                bg(top_half);
                buf += txt;
            } else {
                if (top_half == bottom_half) {
                    bg(top_half);
                    buf += " ";
                } else {
                    bg(top_half);
                    fg(bottom_half);
                    buf += u8"▄";
                }
            }
        }
    }

    std::cout << buf << std::flush;
}

char GameWindow::input()
{
    static const HANDLE stdin_console = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD input = { 0 };
    DWORD numEvents = 0;
    while (true) {
        PeekConsoleInput(stdin_console, &input, 1, &numEvents);
        if (numEvents == 0)
            return 0;
        if (!(input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown == TRUE)) { // consume a non-keydown event
            ReadConsoleInput(stdin_console, &input, 1, &numEvents);
        } else {
            ReadConsoleInput(stdin_console, &input, 1, &numEvents);
            char c = input.Event.KeyEvent.uChar.AsciiChar;
            if (c == '\r')
                return '\n';
            return c;
        }
    }
}

bool GameWindow::draw_internal(const Drawable& drawable, bool write_to_collision_bitmap)
{
    AABB bb = drawable.get_bounding_box();
    int x = bb.left, y = bb.top, w = bb.width, h = bb.height;
    const Color* bitmap = drawable.get_bitmap();
    bool collision = false;

    // i, j track the pixel within the sprite
    // ii, jj track the pixel within the screen
    for (int i = 0, ii = y; i < h && ii < 50; i++, ii++) {
        if (ii < 0)
            continue;
        for (int j = 0, jj = x; j < w && jj < 80; j++, jj++) {
            if (jj < 0)
                continue;
            Color c = bitmap[i * w + j];
            if (c != Color::Transparent) {
                this->bitmap[ii][jj] = c;
                if (this->collision_check_bitmap[ii][jj])
                    collision = true;
                if (write_to_collision_bitmap)
                    this->collision_check_bitmap[ii][jj] = true;
            }
        }
    }
    return collision;
}

void GameWindow::draw(const Drawable& drawable)
{
    draw_internal(drawable, false);
}

bool GameWindow::draw_collision_check(const Drawable& drawable)
{
    return draw_internal(drawable, true);
}

void GameWindow::draw_text(const std::string text, Color color, int x, int y)
{
    if (y < 0 || y >= 25 || x >= 80)
        return;
    for (char c : text) {
        if (x < 80) {
            this->text[y][x] = c;
            this->text_color[y][x] = color;
        }
        x++;
    }
}

void GameWindow::set_title(const std::string title)
{
    std::cout << "\033]2;" << title << "\x07" << std::flush;
}
