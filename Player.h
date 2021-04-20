/** Player.h
 *  Manages player state: animation (walking, flying, dead), score, death, vertical position and
 *  speed.
 *
 *  Player befriends Cactus so that it may have its score (private) modified whenever a cactus
 *  goes off-screen.
 *
 *  Homework: (5) A class that inherits class B (AnimSprite), but which will also define at least
 *                3 other attributes
 *            (6) A class through which to highlight friendship.
 */

#pragma once

#include "AnimSprite.h"

class Player : public AnimSprite {
private:
    double phys_y, phys_vy;
    bool on_the_ground;
    int score;
    bool dead;

    friend class Cactus; // ironic, dar ca sa ne seteze scorul cand trebuie

public:
    Player();

    int get_current_frame() const override;
    void phys_tick();
    void jump();

    int get_score();
    void die();
    bool is_dead();
};
