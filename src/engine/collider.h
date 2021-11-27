
#pragma once
class Collider
{
public:
    static bool is_collision(int x, int y, int w, int h, int bx, int by, int bw, int bh)
    {
        return is_point_in_box(x, y, bx, by, bw, bh) || is_point_in_box(x + w, y, bx, by, bw, bh) || is_point_in_box(x, y + h, bx, by, bw, bh) || is_point_in_box(x + w, y + h, bx, by, bw, bh);
    };

    static bool is_point_in_box(int x, int y, int box_x, int box_y, int box_w, int box_h)
    {
        return x > box_x && (x < (box_x + box_w)) && y > box_y && (y < (box_y + box_h));
    }
};
