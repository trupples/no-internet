#include "HighscoreCounter.h"

HighscoreCounter::HighscoreCounter(int score)
    : is_highscore { true }
    , bitmap { { Color::Transparent } }
    , score { score }
{
    // I do not understand why the above initialisation doesn't just work...
    for (int i = 0; i < 5 * 26; i++)
        bitmap[i] = Color::Transparent;

    const char S[5][6] = {
        "###  ",
        "#   #",
        "###  ",
        "  # #",
        "###  "
    };

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            bitmap[i * 26 + j + 5] = S[i][j] == '#' ? Color::Black : Color::Transparent;
}

void HighscoreCounter::set_mode(bool is_highscore)
{
    this->is_highscore = is_highscore;
}

void HighscoreCounter::set_score(int score)
{
    this->score = score;
}

const Color* HighscoreCounter::get_bitmap() const
{
    const char H[5][5] = {
        "#  #",
        "#  #",
        "####",
        "#  #",
        "#  #"
    };
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 4; j++)
            bitmap[i * 26 + j] = (H[i][j] == '#' && is_highscore) ? Color::Black : Color::Transparent;

    const char digits[10][5][4] = {
        { "###",
            "# #",
            "# #",
            "# #",
            "###" },
        { "  #",
            "  #",
            "  #",
            "  #",
            "  #" },
        { "###",
            "  #",
            "###",
            "#  ",
            "###" },
        { "###",
            "  #",
            "###",
            "  #",
            "###" },
        { "# #",
            "# #",
            "###",
            "  #",
            "  #" },
        { "###",
            "#  ",
            "###",
            "  #",
            "###" },
        { "###",
            "#  ",
            "###",
            "# #",
            "###" },
        { "###",
            "  #",
            "  #",
            "  #",
            "  #" },
        { "###",
            "# #",
            "###",
            "# #",
            "###" },
        { "###",
            "# #",
            "###",
            "  #",
            "###" }
    };

    int score = this->score;
    for (int dig = 3; dig >= 0; dig--) {
        int d = score % 10;
        score /= 10;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                bitmap[i * 26 + dig * 4 + j + 11] = digits[d][i][j] == '#' ? Color::Black : Color::Transparent;
            }
        }
    }

    return bitmap;
}

AABB HighscoreCounter::get_bounding_box() const
{
    return { 52, 2, 26, 5 };
}
