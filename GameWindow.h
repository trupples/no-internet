/** GameWindow.h
 *  Manages console graphics and non-blocking user input. It uses the Drawable interface to
 *  draw arbitrary items regardless of their underlying structure. It implements pixel-perfect
 *  collision checking.
 */

#pragma once

#include "Color.h"
#include "Drawable.h"

#include <string>

class GameWindow {
private:
    Color bitmap[50][80];
    bool collision_check_bitmap[50][80];
    Color text_color[25][80];
    char text[25][80];

    bool draw_internal(const Drawable& drawable, bool write_to_collision_bitmap = false);

public:
    GameWindow();
    ~GameWindow();

    void set_title(const std::string title);

    void begin_frame();
    void draw(const Drawable& drawable);
    bool draw_collision_check(const Drawable& drawable);
    void draw_text(const std::string text, Color color = Color::Black, int x = 0, int y = 0);
    void display_frame();

    char input(); // Non-blocking getchar() basically
};
