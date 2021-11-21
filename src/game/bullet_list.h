#pragma once
#include "bullet.h"

class Bullet_list
{
public:
    Bullet *head = NULL;

    void add_bullet(Window_State window_state, int nx, int ny, int dy, const char *owner_type)
    {
        Bullet *tmp = new Bullet(window_state, nx, ny, dy, owner_type);
        tmp->next = NULL;

        if (head == NULL)
        {
            head = tmp;
            return;
        }

        Bullet *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = tmp;
    }

    void delete_bullet(Bullet *n)
    {
        Bullet *current = head;
        Bullet *prev = NULL;
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
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void refresh_bullets_positions(long dt)
    {
        Bullet *current = head;
        while (current != NULL)
        {
            current->refresh(dt);
            current = current->next;
        }
    }

    void draw_bullets()
    {
        Bullet *current = head;
        while (current != NULL)
        {
            current->draw();
            current = current->next;
        }
    }

    void destroy_remote_bullets()
    {
        Bullet *current = head;
        Bullet *tmp = NULL;
        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            if (tmp->is_need_destroy())
            {
                delete_bullet(tmp);
            }
        }
    }

    void destroy()
    {
        Bullet *current = head;
        Bullet *tmp = NULL;

        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            delete_bullet(tmp);
        }
    }
};