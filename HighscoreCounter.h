/** HighscoreCounter
 *  Another Drawable class that isn't part of the Homework hierarchy, to illustrate the usefulness
 *  of the Drawable interface.
 */

#pragma once

#include "Drawable.h"
#include "Color.h"

class HighscoreCounter : public virtual Drawable {
private:
    mutable Color bitmap[26 * 5];
    bool is_highscore; // Does this count the highscore or just the current score?
    int score;

public:
    HighscoreCounter(int score);
    void set_mode(bool is_highscore);
    void set_score(int score);

    const Color* get_bitmap() const override;
    AABB get_bounding_box() const override;
};
