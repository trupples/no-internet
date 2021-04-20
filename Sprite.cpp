#include "Sprite.h"

Color* bitmap_from_image_data(int width, int height, std::string image_data) {
    Color* bitmap = new Color[width * height];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c = image_data[i * width + j];
            Color col = Color::Transparent;
            switch (c) {
            case '0':
                col = Color::Black;
                break;
            case 'r':
                col = Color::DarkRed;
                break;
            case 'g':
                col = Color::DarkGreen;
                break;
            case 'y':
                col = Color::DarkYellow;
                break;
            case 'b':
                col = Color::DarkBlue;
                break;
            case 'm':
                col = Color::DarkMagenta;
                break;
            case 'c':
                col = Color::DarkCyan;
                break;
            case '2':
                col = Color::LightGray;
                break;
            case '1':
                col = Color::DarkGray;
                break;
            case 'R':
                col = Color::Red;
                break;
            case 'G':
                col = Color::Green;
                break;
            case 'Y':
                col = Color::Yellow;
                break;
            case 'B':
                col = Color::Blue;
                break;
            case 'M':
                col = Color::Magenta;
                break;
            case 'C':
                col = Color::Cyan;
                break;
            case 'W':
                col = Color::White;
                break;
            }
            bitmap[i * width + j] = col;
        }
    }
    return bitmap;
}

Sprite::Sprite(int width, int height, std::string image_data)
    : width(width)
    , height(height)
    , pos { 0, 0 }
    , bitmap(bitmap_from_image_data(width, height, image_data))
{
}

Sprite::Sprite(const Sprite& copy) {
    width = copy.width;
    height = copy.height;
    pos = copy.pos;
    delete[] bitmap;
    bitmap = new Color[width * height];
    memcpy(bitmap, copy.bitmap, sizeof(Color) * width * height);
}

const Color* Sprite::get_bitmap() const
{
    return bitmap;
}

AABB Sprite::get_bounding_box() const
{
    return { pos.x, pos.y, width, height };
}

void Sprite::copy_bitmap(const Sprite& from) {
    delete[] bitmap;

    width = from.width;
    height = from.height;
    bitmap = new Color[width * height];
    memcpy(bitmap, from.bitmap, sizeof(Color) * width * height);
}
