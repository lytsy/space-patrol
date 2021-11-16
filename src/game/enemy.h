#pragma once
#include "../media_types/image.h"
#include "bullet_list.h"

class Enemy
{
public:
    Enemy *next;
    int x, y;
    int dy = 1;
    int dx = 0;
    float x_speed = 0.02;
    float y_speed = 0.15;
    int hp = 2;
    Image *image;

    Enemy(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window)
    {
        window = sdl_window;
        image = new Image(file_name, sdl_renderer);

        init_size();
        init_position();
        dx = rand() % 6 - 3;
        dy = rand() % 2 + 1;
    }

    void init_position()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        SDL_Rect dest;
        image->get_dest(&dest);
        x = rand() % (window_width - dest.w) + dest.w * 0.5;
        y = rand() % window_height * 0.3 * -1;
        image->set_dest_position(x, y);
    }

    void refresh(long dt)
    {
        y += dy * dt * y_speed;
        x += dx * dt * x_speed;
        image->set_dest_position(x, y);
    }

    void init_size()
    {
        int window_width, window_height;
        SDL_GetWindowSize(window, &window_width, &window_height);
        int width = window_width * width_koef_to_screen;
        image->scale_dest_to_width(width);
    }

    void draw()
    {
        image->draw();
    }

    void check_collision(Bullet_list *bullet_list)
    {
        Bullet *current = bullet_list->head;
        while (current != NULL)
        {
            SDL_Rect bullet, enemy;
            current->image->get_dest(&bullet);
            image->get_dest(&enemy);
            bool is_left_top_collision = is_point_in_box(bullet.x, bullet.y,
                                                         enemy.x, enemy.y, enemy.w, enemy.h);
            bool is_right_top_collision = is_point_in_box(bullet.x + bullet.w, bullet.y,
                                                          enemy.x, enemy.y, enemy.w, enemy.h);

            if (is_left_top_collision || is_right_top_collision)
            {
                take_damage(current->damage);
                current->take_damage(current->damage);
            }

            current = current->next;
        }
    }

    bool is_point_in_box(int x, int y, int bx, int by, int bw, int bh)
    {
        return x > bx && (x < (bx + bw)) && y > by && (y < (by + bh));
    }

    void take_damage(int damage)
    {
        hp -= damage;
    }

private:
    SDL_Window *window;
    const char *file_name = "assets/images/enemys/enemy_0.png";
    float width_koef_to_screen = 0.07;
};