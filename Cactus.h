/** Cactus.h
 *  A sprite that can tell if it passed the player, award them some points (it being a friend
 *  class of Player), and change its appearance upon doing so.
 *
 *  Homework: (4-2) Two classes that will inherit the base class, which will define at least 2
 *                  other attributes in addition to those declared in the base class.
 */

#pragma once

#include "Sprite.h"
#include "Player.h"

class Cactus : public Sprite {
    int variant;
    int score;

public:
    Cactus();

    void update(Player &player);
};
