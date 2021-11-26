#pragma once
#include "bullet.h"
#include "base_link_list.h"

class Bullet_list : public Base_Link_List
{
public:
    Bullet *head = nullptr;

    void add(Bullet *node)
    {
        add_node_to_list(node, &head);
    }

    void refresh_bullets_positions(long dt)
    {
        refresh_all(head, dt);
    }

    void draw_bullets()
    {
        draw_all(head);
    }

    void delete_remote_bullets()
    {
        validate_and_clean(&head);
    }

    void destroy()
    {
        destroy_all(&head);
    }
};