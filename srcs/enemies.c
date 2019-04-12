#include <unistd.h>
#include "enemies.h"
#include "doom.h"
#include "serialisation.h"
#include "e_bool.h"

enum e_bool enemy_death(double ms_since_update, t_params params)
{
    t_enemy *enemy;

    enemy = (t_enemy *)params;
    enemy->time_in_death += ms_since_update;
	enemy->object->horizontal_size -= 0.1;
	enemy->object->vertical_size -= 0.1;
	if (enemy->object->horizontal_size <= 0 || enemy->object->vertical_size <= 0)
	{
		enemy->to_destroy = t_true;
		return (t_false);
	}
	return (t_true);
}

void    enemy_hit(t_timer_handler *timer_handler, t_enemy *enemy, Uint32 damage)
{
    enemy->life_remaining -= damage;
    if (enemy->life_remaining <= 0 && (int)enemy->time_in_death <= 0)
    {
    	enemy->time_in_death = 1;
        add_event(
                timer_handler,
                1,
                &enemy_death,
                enemy
        );
    }
}

void	free_enemies(t_enemies *enemies)
{
    int	i;

    i = 0;
    while (i < enemies->count)
    {
        free(enemies->items[i].object);
        i++;
    }
    free(enemies->items);
    free(enemies);
}

void    write_enemy_to_file(int fd, t_enemy enemy)
{
    write_object_to_file(fd, *enemy.object);
    if (write(fd, &enemy.life_remaining, sizeof(enemy.life_remaining)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.heading, sizeof(enemy.heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    write_str_to_file(fd, enemy.front->userdata);
    write_str_to_file(fd, enemy.side->userdata);
}

void    read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy)
{
    if (!(enemy->object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in enemy");
    read_object_from_file(fd, textures, enemy->object);
    if (read(fd, &enemy->life_remaining, sizeof(enemy->life_remaining)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->heading, sizeof(enemy->heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    find_texture_from_file(fd, textures, &enemy->front);
    enemy->object->sprite = enemy->front;
    find_texture_from_file(fd, textures, &enemy->side);
}

void    write_enemies_to_file(int fd, t_enemies *enemies)
{
    int i;

    if (write(fd, &enemies->count, sizeof(enemies->count)) <= 0)
        error_doom("Problem while writing enemies count to file");
    i = 0;
    while (i < enemies->count)
    {
        write_enemy_to_file(fd, enemies->items[i]);
        i++;
    }
}

void    read_enemies_from_file(int fd, t_textures *textures, t_enemies **enemies)
{
    int count;
    int i;

    if (!(*enemies = (t_enemies *)malloc(sizeof(t_enemies))))
        error_doom("Couldn't allocate enemies struct");
    if (read(fd, &count, sizeof(count)) <= 0)
        error_doom("Problem with .roflolilolmao when trying to read enemies");
    (*enemies)->count = count;
    if (!(((*enemies)->items = (t_enemy *)malloc(sizeof(t_enemy) * count))))
        error_doom("Couldn't allocate enemies list");
    i = 0;
    while (i < count)
    {
        read_enemy_from_file(fd, textures, &(*enemies)->items[i]);
        i++;
    }
}
