#pragma once
#include "effect.h"

class Effect_list
{
public:
    Effect *head = NULL;

    Effect_list(Window_State win_state)
    {
        window_state = win_state;
    }

    void add(int nx, int ny, int dy)
    {
        Effect *tmp = new Effect(window_state, nx, ny, dy);
        tmp->next = NULL;

        if (head == NULL)
        {
            head = tmp;
            return;
        }

        Effect *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = tmp;
    }

    void remove(Effect *n)
    {
        Effect *current = head;
        Effect *prev = NULL;
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

    void refresh(long dt)
    {
        Effect *current = head;
        while (current != NULL)
        {
            current->refresh(dt);
            current = current->next;
        }
    }

    void draw()
    {
        Effect *current = head;
        while (current != NULL)
        {
            current->draw();
            current = current->next;
        }
    }

    void destroy_done()
    {
        Effect *current = head;
        Effect *tmp = NULL;
        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            if (tmp->done)
            {
                remove(tmp);
            }
        }
    }

    void destroy()
    {
        Effect *current = head;
        Effect *tmp = NULL;

        while (current != NULL)
        {
            tmp = current;
            current = current->next;
            remove(tmp);
        }
    }

private:
    Window_State window_state;
};