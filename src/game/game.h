#include "../media_types/image.h"
#include "background.h"
#include "bullet_list.h"
#include "enemy_list.h"
#include "player.h"

class Game
{
public:
    int score = 0;
    Background *background;
    Bullet_list *bullet_list;
    Enemy_list *enemy_list;
    Player *player;

    Game(Window_State state)
    {
        background = new Background(state);
        bullet_list = new Bullet_list();
        enemy_list = new Enemy_list(state, bullet_list);
        player = new Player(state, bullet_list);
    }

    void handle_events(long dt, int *keyboard)
    {
        player->handle_keypress(keyboard, dt);
    }

    void refresh(long dt)
    {
        background->refresh(dt);
        player->refresh(engine.dt);
        collisions();

        bullet_list->refresh_bullets_positions(dt);
        bullet_list->destroy_remote_bullets();

        enemy_list->refresh_enemys_positions(dt);
        enemy_list->delete_dead_enemys();
        enemy_list->spawn_enemys();
    }

    void draw()
    {
        background->draw();
        enemy_list->draw_enemys();
        bullet_list->draw_bullets();
        player->draw();
    }

    void destroy()
    {
        background->destroy();
        player->destroy();
        enemy_list->destroy();
        bullet_list->destroy();
    }

    void collisions()
    {
        Enemy *enemy;
        Bullet *bullet;

        bullet = bullet_list->head;
        while (bullet != NULL)
        {
            process_collision(player, bullet);
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