#include <unistd.h>
#include "enemies.h"
#include "doom.h"
#include "serialisation.h"

void    write_enemy_to_file(int fd, t_enemy enemy)
{
    write_object_to_file(fd, *enemy.object);
    if (write(fd, &enemy.hp, sizeof(enemy.hp)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.heading, sizeof(enemy.heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write_str_to_file(fd, enemy.front->userdata) < 0)
        error_doom("Couldn't find enemy front texture");
    if (write_str_to_file(fd, enemy.side->userdata) < 0)
        error_doom("Couldn't find enemy side texture");
}

void    read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy)
{
    if (!(enemy->object = (t_object *)malloc(sizeof(t_object))))
        error_doom("Couldn't allocate object in enemy");
    read_object_from_file(fd, textures, enemy->object);
    if (read(fd, &enemy->hp, sizeof(enemy->hp)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->heading, sizeof(enemy->heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (find_texture_from_file(fd, textures, &enemy->front) < 0)
        error_doom("Couldn't find enemy front texture");
    enemy->object->sprite = enemy->front;
    if (find_texture_from_file(fd, textures, &enemy->side) < 0)
        error_doom("Couldn't find enemy side texture");
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