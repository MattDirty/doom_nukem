#include <unistd.h>
#include "enemies.h"
#include "doom.h"
#include "serialisation.h"

void    write_enemy_to_file(int fd, t_enemy enemy)
{
    if (write(fd, &enemy.object->x, sizeof(enemy.object->x)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.object->y, sizeof(enemy.object->y)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.object->z, sizeof(enemy.object->z)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.object->horizontal_size, sizeof(enemy.object->horizontal_size)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.object->vertical_size, sizeof(enemy.object->vertical_size)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.hp, sizeof(enemy.hp)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.heading, sizeof(enemy.heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write(fd, &enemy.heading, sizeof(enemy.heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (write_str_to_file(fd, enemy.front->userdata) < 0)
        error_doom("Couldn't find enemy front texture");
    if (write_str_to_file(fd, enemy.side->userdata) < 0)
        error_doom("Couldn't find enemy front texture");
}

void    read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy)
{
    if (read(fd, &enemy->object->x, sizeof(enemy->object->x)) <= 0)
            error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->object->y, sizeof(enemy->object->y)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->object->z, sizeof(enemy->object->z)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->object->horizontal_size, sizeof(enemy->object->horizontal_size)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->object->vertical_size, sizeof(enemy->object->vertical_size)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->hp, sizeof(enemy->hp)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->heading, sizeof(enemy->heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (read(fd, &enemy->heading, sizeof(enemy->heading)) <= 0)
        error_doom("Problem while reading enemy from file");
    if (find_texture_from_file(fd, textures, &enemy->front) < 0)
        error_doom("Couldn't find enemy front texture");
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

    if (!(*enemies = (t_enemies *)malloc(sizeof(t_enemy))))
        error_doom("Couldn't allocate enemies struct");
    if (read(fd, &count, sizeof(count)) <= 0)
        error_doom("Problem with .roflolilolmao when trying to read enemies");
    (*enemies)->count = count;
    if (!(((*enemies)->items = (t_enemy *)malloc(sizeof(t_enemy) * count))))
        error_doom("Couldn't allocate enemies list");
    i = 0;
    while (i < (*enemies)->count)
    {
        read_enemy_from_file(fd, textures, &(*enemies)->items[i]);
        i++;
    }
}