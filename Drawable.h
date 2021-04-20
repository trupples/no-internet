/** Drawable.h
 *  An interface for anything to be drawn to the screen.
 *
 *  Homework: (1) An interface that defines at least 2 pure virtual methods.
 */

#pragma once

#include "Color.h"

struct AABB { // Axially Aligned Bounding Box
    int left, top, width, height;
};

class Drawable {
public:
    virtual const Color* get_bitmap() const = 0;
    virtual AABB get_bounding_box() const = 0;
};
