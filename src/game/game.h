#include "../media_types/image.h"
#include "enemy_list.h"
#include "bullet_list.h"
#include "player.h"

class Game
{
public:
    int score = 0;
    Game() {}

    void collisions(Player player, Bullet_list *bullet_list, Enemy_list *enemy_list)
    {
        Enemy *enemy;
        Bullet *bullet;

        bullet = bullet_list->head;
        while (bullet != NULL)
        {
            process_collision(&player, bullet);
            enemy = enemy_list->head;
            while (enemy != NULL)
            {
                process_collision(enemy, bullet);
                enemy = enemy->next;
            }
            bullet = bullet->next;
        }
    }

    void process_collision(Character *character, Bullet *bullet)
    {
        bool collided = character->is_colllided(bullet);
        if (collided)
        {
            character->on_collide(bullet);
            bullet->on_collide();
            bool is_player_shoot = strcmp(bullet->owner_type, "player") == 0;
            if (character->is_damage_was_lethal(bullet) && is_player_shoot)
            {
                score++;
            }
        }
    }
};