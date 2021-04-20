/** AnimSprite.h
 *  A specialized sprite that divides its bitmap into logical animation frames.
 *
 *  Homework: (4-1) Two classes that will inherit the base class, which will define at least 2
 *                  other attributes in addition to those declared in the base class.
 */

#pragma once

#include "Sprite.h"

class AnimSprite : public Sprite {
protected:
    int frames;
    double frame_time;
    double animation_start;

public:
    AnimSprite(int width, int height, int frames, double frame_time, std::string image_data);

    const Color* get_bitmap() const override;

    virtual int get_current_frame() const;
    void reset_anim();
};
