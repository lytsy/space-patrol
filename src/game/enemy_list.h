#pragma once
#include "enemy.h"
#include "bullet_list.h"

class Enemy_list
{
public:
    Enemy *head = NULL;
    int length = 0;

    Enemy_list(Window_State win_state, Bullet_list *list)
    {
        window_state = win_state;
        screen = window_state.screen;
        bullet_list = list;
    }

    void add_enemy()
    {
        Enemy *tmp = new Enemy(window_state, bullet_list);
        tmp->next = NULL;

        if (head == NULL)
        {
            head = tmp;
            length++;
            return;
        }

        Enemy *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = tmp;
        length++;
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
                current->destroy();
                free(current);
                length--;
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

    void spawn_enemys()
    {
        int must_be_enemys = 4;
        int need_add_enemys = must_be_enemys - length;
        while (need_add_enemys > 0)
        {
            add_enemy();
            need_add_enemys--;
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

    void delete_dead_enemys()
    {
        Enemy *current = head;
        Enemy *tmp = NULL;

        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            if (tmp->is_need_destroy())
            {
                delete_enemy(tmp);
            }
        }
    }

    void destroy()
    {
        Enemy *current = head;
        Enemy *tmp = NULL;

        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            delete_enemy(tmp);
        }
    }

private:
    Window_State window_state;
    Screen *screen;
    Bullet_list *bullet_list = NULL;
};