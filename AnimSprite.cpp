#include "AnimSprite.h"
#include "Timer.h"

AnimSprite::AnimSprite(int width, int height, int frames, double frame_time, std::string image_data)
    : Sprite::Sprite(width, height * frames, image_data)
    , frames(frames)
    , frame_time(frame_time)
    , animation_start(Timer::now())
{
    // Correct the Sprite::Sprite constructor which thinks this is very tall sprite
    this->height = height;
}

const Color* AnimSprite::get_bitmap() const
{
    return &bitmap[get_current_frame() * width * height];
}

int AnimSprite::get_current_frame() const
{
    double t = Timer::now() - animation_start;
    return (int)(t / frame_time) % frames;
}

void AnimSprite::reset_anim()
{
    animation_start = Timer::now();
}
