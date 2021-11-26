#pragma once
#include "enemy.h"
#include "base_link_list.h"

class Enemy_list : public Base_Link_List
{
public:
    Enemy *head = NULL;

    void add(Enemy *node)
    {
        add_node_to_list(node, &head);
    }

    void refresh_enemys(long dt)
    {
        refresh_all(head, dt);
    }

    void draw_enemys()
    {
        draw_all(head);
    }

    void delete_dead_enemys()
    {
        validate_and_clean(&head);
    }

    void destroy()
    {
        destroy_all(&head);
    }
};