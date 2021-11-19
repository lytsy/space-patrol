#pragma once
#include "enemy.h"
#include "bullet_list.h"

class Enemy_list
{
public:
    Enemy *head = NULL;

    Enemy_list(SDL_Renderer *sdl_renderer, SDL_Window *sdl_window, Screen *engine_screen, Bullet_list *list)
    {
        window = sdl_window;
        renderer = sdl_renderer;
        bullet_list = list;
        screen = engine_screen;
    }

    void add_enemy()
    {
        Enemy *tmp = new Enemy(renderer, window, screen, bullet_list);
        tmp->next = NULL;

        if (head == NULL)
        {
            head = tmp;
            return;
        }

        Enemy *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = tmp;
    }

    void delete_enemy(Enemy *n)
    {
        Enemy *current = head;
        Enemy *prev = NULL;
        while (current != NULL)
        {
            if (current == n)
            {
                if (prev == NULL)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void refresh_enemys_positions(long dt)
    {
        Enemy *current = head;
        while (current != NULL)
        {
            current->refresh(dt);
            current = current->next;
        }
    }

    void draw_enemys()
    {
        Enemy *current = head;
        while (current != NULL)
        {
            current->draw();
            current = current->next;
        }
    }

    void destroy_enemys()
    {
        Enemy *current = head;
        Enemy *tmp = NULL;

        if (window == NULL)
        {
            return;
        }

        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            if (tmp->y > screen->w || tmp->hp <= 0)
            {
                delete_enemy(tmp);
            }
        }
    }

    void spawn_enemys()
    {
        int enemys_counter = 0;
        Enemy *current = head;
        while (current != NULL)
        {
            enemys_counter++;
            current = current->next;
        }

        int must_be_enemys = 4;

        int need_add_enemys = must_be_enemys - enemys_counter;
        while (need_add_enemys > 0)
        {
            need_add_enemys--;
            add_enemy();
        }
    }

    void check_collision(Bullet_list *bullet_list)
    {
        Enemy *enemy = head;
        while (enemy != NULL)
        {
            enemy->check_collision(bullet_list);
            enemy = enemy->next;
        }
    }

private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Bullet_list *bullet_list = NULL;
    Screen *screen;
};