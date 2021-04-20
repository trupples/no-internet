/** Sprite.h
 *  The base class for all actual graphics. It is a Drawable with a Position, dimensions, and a
 *  bitmap image.
 *
 *  Homework: (3) A base class that will:
 *                (a) Use the interface defined in point 1
 *                (b) Define at least 3 attributes, but also an attribute of the type of the final
 *                    class at point 2.
 */

#pragma once

#include "Color.h"
#include "Drawable.h"
#include "Position.h"

class Sprite : public virtual Drawable {
protected:
    int width, height;
    Color* bitmap;

public:
    Position pos;
    Sprite(int w, int h, std::string image_data);
    Sprite(const Sprite& copy);

    void copy_bitmap(const Sprite& from);

    const Color* get_bitmap() const override;
    AABB get_bounding_box() const override;
};

Color* bitmap_from_image_data(int width, int height, std::string image_data);
