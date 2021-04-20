#include "Cactus.h"
#include "GameWindow.h"
#include "HighscoreCounter.h"
#include "Player.h"
#include "Timer.h"

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h> // just for srand(time(0))

// Generates a sky and random ground texture data string
std::string generate_background(int w)
{
    std::string bg;
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < w; j++)
            bg += 'C';
    }
    for (int j = 0; j < w; j++)
        bg += '0';
    for (int i = 41; i < 50; i++) {
        for (int j = 0; j < w; j++) {
            char c = 'y';
            if (rand() % 100 < 1)
                c = '1';
            if (rand() % 100 < 1)
                c = '2';
            if (rand() % 100 < 1)
                c = 'W';
            if (rand() % 100 < 1)
                c = 'Y';
            bg += c;
        }
    }
    return bg;
}

// Classic "yield to other processes until the time comes for a new frame" loop
#define REGULATE_FPS(FPS)                                    \
    {                                                        \
        double now = Timer::now();                           \
        if (now - last > 1. / FPS) {                         \
            std::stringstream ss;                            \
            ss << "No Internet | FPS: " << 1 / (now - last); \
            gameWindow.set_title(ss.str());                  \
            last = now;                                      \
        } else {                                             \
            Sleep(0);                                        \
            continue;                                        \
        }                                                    \
    }

// Updates the high_score variable and/or the high-score.txt file with the greater of the two
void sync_high_score(int& high_score)
{
    std::ifstream f("high-score.txt");
    if (f) {
        int file_high_score;
        f >> file_high_score;
        if (high_score < file_high_score)
            high_score = file_high_score;
    }
    f.close();

    std::ofstream g("high-score.txt");
    g << high_score;
    g.close();
}

int main()
{
    srand(time(0));

    GameWindow gameWindow;
    Sprite background(200, 50, generate_background(200));
    int high_score = 0;
    sync_high_score(high_score);

    // Game loop: shows start screen, plays game, shows death screen, repeats
    while (true) {
        Player player;
        HighscoreCounter hs(high_score);
        Cactus cactus;

        auto draw_background = [&]() {
            gameWindow.draw(background);
            background.pos.x += 200;
            gameWindow.draw(background);
            background.pos.x -= 200;
        };

        // Start scene - draw static stuff until space is pressed
        double last = Timer::now();
        do {
            REGULATE_FPS(30);

            gameWindow.begin_frame();
            draw_background();
            gameWindow.draw(cactus);

            // Reset animation before drawing so it's "stuck" in the first walking animation frame
            player.reset_anim();
            gameWindow.draw(player);

            gameWindow.draw(hs);
            gameWindow.draw_text("Press space to start!", Color::Black, 2, 23);
            gameWindow.draw_text("By @_trupples", Color::Black, 65, 23);

            gameWindow.display_frame();
        } while (gameWindow.input() != ' ');

        // Prepare actual game
        hs.set_mode(false);
        player.jump();

        // Play until player dies
        while (!player.is_dead()) {
            REGULATE_FPS(30);

            gameWindow.begin_frame();

            cactus.update(player);
            hs.set_score(player.get_score());

            background.pos.x = (background.pos.x - 1) % 200;
            draw_background();

            gameWindow.draw_collision_check(cactus);
            if (gameWindow.draw_collision_check(player)) {
                player.die();
            }

            gameWindow.draw(hs);

            gameWindow.display_frame();

            if (gameWindow.input() == ' ')
                player.jump();
            player.phys_tick();
        }

        // Update high score
        if (player.get_score() > high_score) {
            high_score = player.get_score();
            sync_high_score(high_score);
        }

        // Draw the death screen
        gameWindow.begin_frame();
        draw_background();
        gameWindow.draw(cactus);
        gameWindow.draw(player);
        gameWindow.draw(hs);
        gameWindow.display_frame();

        // Cinematic screen shake
        gameWindow.shake(50);

        // And wait 5 seconds
        double death_screen_begin = Timer::now();
        while (Timer::now() - death_screen_begin < 5) {
            Sleep(10);
        }

        // Consume all input so keypresses that happened during the death scene don't trigger the start of the next game
        while (gameWindow.input())
            ;
    }

    return 0;
}
