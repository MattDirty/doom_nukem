#include <unistd.h>
#include "enemies.h"
#include "doom.h"
#include "serialisation.h"
#include "e_bool.h"
#include "sectors.h"

void	add_enemy(
        t_linked_enemies **linked_enemies,
        t_linked_enemies *enemy)
{
    t_linked_enemies	*node;

    if (!*linked_enemies)
    {
        *linked_enemies = enemy;
        return;
    }
    node = *linked_enemies;
    while (node->next)
        node = node->next;
    node->next = enemy;
}

t_linked_enemies	*extract_enemy(
        t_linked_enemies **linked_enemies,
        t_enemy *enemy)
{
    t_linked_enemies	*previous;
    t_linked_enemies	*node;

    if (enemy == &(*linked_enemies)->item)
    {
        previous = *linked_enemies;
        *linked_enemies = previous->next;
        return (previous);
    }
    previous = NULL;
    node = *linked_enemies;
	while (node)
	{
        if (&node->item == enemy)
        {
            previous->next = node->next;
            return (node);
        }
        previous = node;
        node = node->next;
	}
    return NULL;
}

void	delete_enemy(
        t_linked_enemies **linked_enemies,
        t_enemy *enemy)
{
    t_linked_enemies	*node;

    node = extract_enemy(linked_enemies, enemy);
    if (!node)
        return;
    free(node->item.object);
    free(node);
}

enum e_bool enemy_death(double ms_since_update, t_params params)
{
    t_enemy *enemy;
    int     step;

    enemy = (t_enemy *)params;
    enemy->time_in_death += ms_since_update;

    step = (int)(enemy->time_in_death) / (int)(enemy->death_duration / 16);
    if (step >= 16)
        step = 15;
    enemy->object->sprite = enemy->explosion[step];
	if (enemy->time_in_death >= enemy->death_duration)
	{
		enemy->to_destroy = t_true;
		return (t_false);
	}
	return (t_true);
}

void    damage_enemy(t_timer_handler *timer_handler, t_enemy *enemy, Uint32 damage)
{
    enemy->life_remaining -= damage;
    if (enemy->life_remaining <= 0 && (int)enemy->time_in_death <= 0)
    {
        enemy->death_duration = 1700;
    	enemy->time_in_death = 1;
        add_event(
                timer_handler,
                1,
                &enemy_death,
                enemy
        );
    }
}

void	free_enemies(t_linked_enemies *enemies)
{
    if (!enemies)
        return;
    free_enemies(enemies->next);
    free(enemies->item.object);
    free(enemies);
}

void    write_enemy_to_file(int fd, t_enemy enemy)
{
    write_object_to_file(fd, *enemy.object);
    if (write(fd, &enemy.life_remaining, sizeof(enemy.life_remaining)) <= 0)
        error_doom("Problem while reading enemy from file");
	if (write(fd, &enemy.death_duration, sizeof(enemy.death_duration)) <= 0)
		error_doom("Problem while reading enemy from file");
	if (write(fd, &enemy.time_in_death, sizeof(enemy.time_in_death)) <= 0)
		error_doom("Problem while reading enemy from file");
	if (write(fd, &enemy.to_destroy, sizeof(enemy.to_destroy)) <= 0)
		error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.heading, sizeof(enemy.heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.type, sizeof(enemy.type)) <= 0)
        error_doom("Problem while type enemy from file");
    write_str_to_file(fd, enemy.front->userdata);
    write_str_to_file(fd, enemy.side->userdata);
    write_str_to_file(fd, enemy.back->userdata);
    write_str_to_file(fd, enemy.explosion[0]->userdata);
    write_str_to_file(fd, enemy.explosion[1]->userdata);
    write_str_to_file(fd, enemy.explosion[2]->userdata);
    write_str_to_file(fd, enemy.explosion[3]->userdata);
    write_str_to_file(fd, enemy.explosion[4]->userdata);
    write_str_to_file(fd, enemy.explosion[5]->userdata);
    write_str_to_file(fd, enemy.explosion[6]->userdata);
    write_str_to_file(fd, enemy.explosion[7]->userdata);
    write_str_to_file(fd, enemy.explosion[8]->userdata);
    write_str_to_file(fd, enemy.explosion[9]->userdata);
    write_str_to_file(fd, enemy.explosion[10]->userdata);
    write_str_to_file(fd, enemy.explosion[11]->userdata);
    write_str_to_file(fd, enemy.explosion[12]->userdata);
    write_str_to_file(fd, enemy.explosion[13]->userdata);
    write_str_to_file(fd, enemy.explosion[14]->userdata);
    write_str_to_file(fd, enemy.explosion[15]->userdata);
 }

static void	init_enemy_from_type(t_enemy *enemy)
{
    if (enemy->type == et_boss)
    {
        enemy->act = boss_intelligence;
        enemy->speed = 0.01;
    }
    else if (enemy->type == et_brazil)
    {
        enemy->act = basic_enemy_intelligence;
        enemy->speed = 0.1;
    }
    else
        error_doom("invalid enemy");
}

void    read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy)
{
    if (!(enemy->object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in enemy");
    read_object_from_file(fd, textures, enemy->object);
    if (read(fd, &enemy->life_remaining, sizeof(enemy->life_remaining)) <= 0)
        error_doom("Problem while reading enemy from file");
	if (read(fd, &enemy->death_duration, sizeof(enemy->death_duration)) <= 0)
		error_doom("Problem while reading enemy from file");
	if (read(fd, &enemy->time_in_death, sizeof(enemy->time_in_death)) <= 0)
		error_doom("Problem while reading enemy from file");
	if (read(fd, &enemy->to_destroy, sizeof(enemy->to_destroy)) <= 0)
		error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->heading, sizeof(enemy->heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->type, sizeof(enemy->type)) <= 0)
        error_doom("Problem while reading enemy from file");
    init_enemy_from_type(enemy);
    find_texture_from_file(fd, textures, &enemy->front);
    enemy->object->sprite = enemy->front;
    find_texture_from_file(fd, textures, &enemy->side);
    find_texture_from_file(fd, textures, &enemy->back);
    find_texture_from_file(fd, textures, &(enemy->explosion[0]));
    find_texture_from_file(fd, textures, &(enemy->explosion[1]));
    find_texture_from_file(fd, textures, &(enemy->explosion[2]));
    find_texture_from_file(fd, textures, &(enemy->explosion[3]));
    find_texture_from_file(fd, textures, &(enemy->explosion[4]));
    find_texture_from_file(fd, textures, &(enemy->explosion[5]));
    find_texture_from_file(fd, textures, &(enemy->explosion[6]));
    find_texture_from_file(fd, textures, &(enemy->explosion[7]));
    find_texture_from_file(fd, textures, &(enemy->explosion[8]));
    find_texture_from_file(fd, textures, &(enemy->explosion[9]));
    find_texture_from_file(fd, textures, &(enemy->explosion[10]));
    find_texture_from_file(fd, textures, &(enemy->explosion[11]));
    find_texture_from_file(fd, textures, &(enemy->explosion[12]));
    find_texture_from_file(fd, textures, &(enemy->explosion[13]));
    find_texture_from_file(fd, textures, &(enemy->explosion[14]));
    find_texture_from_file(fd, textures, &(enemy->explosion[15]));
}

void    write_enemies_to_file(int fd, t_linked_enemies *enemies)
{
    enum e_bool	next;

    next = enemies != NULL;
    if (write(fd, &next, sizeof(next)) <= 0)
        error_doom("mabite");
    if (!next)
        return;
    write_enemy_to_file(fd, enemies->item);
    write_enemies_to_file(fd, enemies->next);
}

void    read_enemies_from_file(
        int fd,
        t_textures *textures,
        t_linked_enemies **enemies)
{
    enum e_bool	next;

    if (read(fd, &next, sizeof(next)) <= 0)
        error_doom("The shield has gone mad, Quercus!");
    if (!next)
        return;
    if (!(*enemies = (t_linked_enemies*)malloc(sizeof(t_linked_enemies))))
        error_doom("Couldn't allocate enemies struct");
    (*enemies)->next = NULL;
    read_enemy_from_file(fd, textures, &(*enemies)->item);
    read_enemies_from_file(fd, textures, &(*enemies)->next);
}
