#include "Cactus.h"

const Sprite cactus_sprites[5] = {
    Sprite(17, 16,
        "-------ggg-------"
        "------ggggg------"
        "-----ggggGgg---g-"
        "-----gGggggg--gg-"
        "-----gGggggg-MMgg"
        "-----gggGggg-MMgg"
        "-M---gggGggg-gggg"
        "MMM--gggggGgggggg"
        "-Mg--gggggGggggg-"
        "-gg--ggGgggggg---"
        "-ggg-ggggGgg-----"
        "--gggggggGgg-----"
        "---gggGggggg-----"
        "-----gGggggg-----"
        "-----gggggGg-----"
        "-----ggggggg-----"),

    Sprite(25, 23,
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------------------------"
        "-------222WWWWWWW--------"
        "------222WWWWWWWWWWWW----"
        "------22WWW11WWWWWWW22---"
        "------2WWW100WWWW1WW222--"
        "------WWWW100WWW101W2222-"
        "------WWWW100WW100WWW2222"
        "-----WWWWWWWWWW100WWW2222"
        "----W11WW1WWWWWWWWWW-222-"
        "--WW11WW11WWWWWWWW---222-"
        "WWWWWWW1WWWWWWWWWW---22--"
        "WWWWWWWW------------22---"
        "----------WWWWWW---------"
        "--------WWWWWWWW---------"
        "---WWWWWWWWWWWW----------"
    ),

    Sprite(23, 18,
        "-----------------------"
        "-----------------------"
        "-----------------------"
        "-----------------------"
        "-----------------------"
        "-----------------------"
        "--------ggg--------gg--"
        "--------ggg--------ggg-"
        "-------gggg--------ggg-"
        "-------RRRg--------RGR-"
        "-------RGRgg-------gRgg"
        "---g---RRRgg---gg-ggggg"
        "---g---ggggg---RR-ggggg"
        "--ggg--ggggg--gRG-ggggg"
        "--gRg-gggRRRg-ggggggggg"
        "-gRRR-gggRGRgggggggggGg"
        "-gRGR-ggggRRggggGgggggg"
        "gggggggGggggggggggggggg"),

    Sprite(6, 19,
        "------"
        "------"
        "--yy--"
        "--yy--"
        "--gg--"
        "--gg--"
        "-gggg-"
        "-gggg-"
        "gggggg"
        "gggggg"
        "g0gg0g"
        "gg00gg"
        "gg00gg"
        "g0gg0g"
        "gggggg"
        "gggggg"
        "gggggg"
        "gggggg"
        "-gggg-"),

    Sprite(32, 25,
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "--------------------------------"
        "----------WWW-------------------"
        "--------WWW----WW---------------"
        "-------W------W-----------------"
        "------W-------W--WW--W----------"
        "------W------W----W-W-W-W-------"
        "------W-----WW----WW--W-WW------"
        "------W-----W----W-W--W-WW------"
        "------W-----W----W-W--W-W-W-----"
        "------W-----W---W--W--W---W-----"
        "------W-----W---W--W--W---W-----"
        "------W-----W---W--W--W---W-----"
        "W-----WW----W---WW-W--W---W-----"
        "WWW----W-----W----W--WW--WW--WWW"
        "--WW-------------WW-WW---W------"
        "---WWWWW----WWW--W--W---W-------"
        "----------------W---------------")
};

Cactus::Cactus()
    : Sprite::Sprite(cactus_sprites[0])
    , variant(0)
    , score(20)
{
    pos.x = 25;
    pos.y = 24;
}

void Cactus::update(Player& player)
{
    pos.x--;
    if (pos.x < -width) {
        // Can only add to player.score because we're friends
        player.score += score;

        // Pick a new variant
        variant = rand() % 5;

        // Figure out how many points it's worth
        if (variant == 1 || variant == 4) {
            score = 1;
        } else if (variant == 0 || variant == 3) {
            score = 2;
        } else if (variant == 2) {
            score = 3;
        }

        // And copy its bitmap
        copy_bitmap(cactus_sprites[variant]);
        
        pos.x = 80;
        pos.y = 24;
    }
}
