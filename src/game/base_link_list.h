
#pragma once
class Base_Link_List
{
public:
    int length = 0;

protected:
    template <class Node>
    void add_node_to_list(Node node, Node *list_head)
    {
        node->next = nullptr;

        if (*list_head == nullptr)
        {
            *list_head = node;
            length++;
            return;
        }

        Node current = *list_head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = node;
        length++;
    }

    template <class Node>
    void remove_node_from_list(Node node, Node *list_head)
    {
        Node current = *list_head;
        Node prev = nullptr;
        while (current != nullptr)
        {
            if (current == node)
            {
                if (prev == nullptr)
                {
                    *list_head = current->next;
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

    template <class Node>
    void draw_all(Node list_head)
    {
        Node current = list_head;
        while (current != nullptr)
        {
            current->draw();
            current = current->next;
        }
    }

    template <class Node>
    void refresh_all(Node list_head, long dt)
    {
        Node current = list_head;
        while (current != nullptr)
        {
            current->refresh(dt);
            current = current->next;
        }
    }

    template <class Node>
    void validate_and_clean(Node *list_head)
    {
        Node current = *list_head;
        Node tmp = nullptr;
        while (current != nullptr)
        {
            tmp = current;
            current = current->next;
            if (tmp->is_need_destroy())
            {
                remove_node_from_list(tmp, list_head);
            }
        }
    }

    template <class Node>
    void destroy_all(Node *list_head)
    {
        Node current = *list_head;
        Node tmp = nullptr;

        while (current != nullptr)
        {
            tmp = current;
            current = current->next;
            remove_node_from_list(tmp, list_head);
        }
    }
};