#include "math-plotter.hpp"
#include <cmath>

gearoenix::math::Plotter::Brush::Brush(const int thickness, const std::uint32_t color)
    : color(color)
{
    const int radius2 = thickness * thickness;
    for (int x = -thickness; x <= thickness; ++x) {
        for (int y = -thickness; y <= thickness; ++y) {
            if (x * x + y * y <= radius2) {
                indices.push_back(std::make_tuple(x, y));
            }
        }
    }
}

void gearoenix::math::Plotter::plot(const int x, const int y, const Brush& b)
{
    for (const std::tuple<int, int>& i : b.indices) {
        const int xi = std::get<0>(i) + x;
        if (xi < 0 || xi > img_width)
            continue;
        const int yi = std::get<1>(i) + y;
        if (yi < 0 || yi > img_height)
            continue;
        pixels[xi + yi * img_height] = b.color;
    }
}

gearoenix::math::Plotter::Plotter(std::uint32_t* const pixels, const int img_width, const int img_height)
    : pixels(pixels)
    , img_width(img_width)
    , img_height(img_height)
{
}

void gearoenix::math::Plotter::draw_point(const Vec2& pos, const Brush& b)
{
    const int x = static_cast<int>(std::round(pos[0]));
    const int y = static_cast<int>(std::round(pos[1]));
    plot(x, y, b);
}

void gearoenix::math::Plotter::draw_line(const Vec2& start, const Vec2& end, const Brush& b)
{
    //    Vec2 d = end - start;
    int x0 = (int)std::round(start[0]);
    int y0 = (int)std::round(start[1]);
    int x1 = (int)std::round(end[0]);
    int y1 = (int)std::round(end[1]);
    //    if(x0 > x1 || (x0 == x1 && y0 > y1)) {
    //        int tmp = x0;
    //        x0 = x1;
    //        x1 = tmp;
    //        tmp = y0;
    //        y0 = y1;
    //        y1 = tmp;
    //        d = -d;
    //    }
    int dx = x1 - x0;
    dx = dx < 0 ? -dx : dx;
    int dy = y1 - y0;
    dy = dy < 0 ? -dy : dy;
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy, e2;
    for (; x0 != x1 || y0 != y1;) {
        plot(x0, y0, b);
        e2 = err << 1;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}
