#pragma once
#include "effect.h"
#include "base_link_list.h"

class Effect_list : public Base_Link_List
{
public:
    Effect *head = NULL;

    void add(Effect *node)
    {
        add_node_to_list(node, &head);
    }

    void refresh(long dt)
    {
        refresh_all(head, dt);
    }

    void draw()
    {
        draw_all(head);
    }

    void delete_done()
    {
        validate_and_clean(&head);
    }

    void destroy()
    {
        destroy_all(&head);
    }
};