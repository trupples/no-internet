#include "Player.h"
#include "Timer.h"

Player::Player()
    : AnimSprite::AnimSprite(13, 16, 5, .1,
        // Walk 0
        "-------WWWW--"
        "-------WW0W--"
        "-------WWWW--"
        "-------WWWYYY"
        "-------WWWRR-"
        "-WWWWWWWWW---"
        "WWWWWWWW2WW--"
        "WWWWWWWW2WW--"
        "WWWWWWW2WWW--"
        "WW22222WWWW--"
        "-WWWWWWWWWW--"
        "--WWWWWWWW---"
        "----WWWW-----"
        "----Y--------"
        "----Y--------"
        "---YYYYY-----"

        // Walk 1
        "-------WWWW--"
        "-------WW0W--"
        "-------WWWW--"
        "-------WWWYYY"
        "-------WWWRR-"
        "-WWWWWWWWW---"
        "WWWWWWWW2WW--"
        "WWWWWWWW2WW--"
        "WWWWWWW2WWW--"
        "WW22222WWWW--"
        "-WWWWWWWWWW--"
        "--WWWWWWWW---"
        "---YWWWW-----"
        "Y-Y---Y------"
        "-Y-----Y-Y---"
        "--YY---YY----"

        // Fly 0
        "WWW----WWWW--"
        "WWWW-22WW0W--"
        "WWWW222WWWW--"
        "WWWWW22WWWYYY"
        "-WWWW22WWWRR-"
        "-WWWWWWWWW---"
        "W2WWWWWWWWW--"
        "WW2WWWWWWWW--"
        "WWW22WWWWWW--"
        "WWWWWWWWWWW--"
        "-WWWWWWWWWW--"
        "--WWWWWWWW---"
        "---YWWWW-----"
        "Y-Y---Y------"
        "-Y-----Y-Y---"
        "--YY---YY----"

        // Fly 1
        "-------WWWW--"
        "-------WW0W--"
        "-------WWWW--"
        "-WW---2WWWYYY"
        "WWWWW22WWWRR-"
        "-WWWWWWWWW---"
        "W2WWWWWWWWW--"
        "W2WWWWWWWWW--"
        "WW22WWWWWWW--"
        "WWW222WWWWW--"
        "-WWWWWWWWWW--"
        "--WWWWWWWW---"
        "---YWWWW-----"
        "Y-Y---Y------"
        "-Y-----Y-Y---"
        "--YY---YY----"

        // Dead
        "WWW----W0W0--"
        "WWWW-22WW0W--"
        "WWWW222W0W0--"
        "WWWWW22WWWYYY"
        "-WWWW22WWW--R"
        "-WWWWWWWWW--R"
        "W2WWWWWWWWW--"
        "WW2WWWWWWWW--"
        "WWW22WWWWWW--"
        "WWWWWWWWWWW--"
        "-WWWWWWWWWW--"
        "--WWWWWWWW---"
        "---YWWWW-----"
        "Y-Y---Y------"
        "-Y-----Y-Y---"
        "--YY---YY----")
    , phys_y(0)
    , phys_vy(0)
    , on_the_ground(true)
    , score(0)
    , dead(false)
{
    pos.x = 3;
    pos.y = 24;
}

int Player::get_current_frame() const
{
    double t = Timer::now() - animation_start;
    if (dead)
        return 4;
    if (on_the_ground) {
        return (int)(t / frame_time) % 2;
    } else {
        return 2 + (int)(t / frame_time) % 2;
    }
}

void Player::phys_tick()
{
    if (dead)
        return;
    phys_y += phys_vy;
    phys_vy -= 0.1;
    if (phys_vy < 0) { // slow down fall
        phys_vy *= 0.85;
    }
    if (phys_y <= 0) {
        phys_y = 0;
        phys_vy = 0;
        on_the_ground = true;
    }
    pos.y = (int)(24 - phys_y);
}

void Player::jump()
{
    if (on_the_ground) {
        phys_vy = 2.05;
        on_the_ground = false;
    }
}

int Player::get_score() {
    return score;
}

void Player::die() {
    dead = true;
}

bool Player::is_dead() {
    return dead;
}
