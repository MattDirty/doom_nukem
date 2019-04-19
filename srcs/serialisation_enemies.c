/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serialisation_enemies.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:48:41 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 04:48:43 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "enemies.h"
#include "basic_enemies_intelligence.h"
#include "doom.h"
#include "serialisation.h"

static void	init_enemy_from_type(t_enemy *enemy)
{
	enemy->animation_time = 0;
	enemy->object->sprite = enemy->front;
	if (enemy->type == et_boss)
	{
		enemy->life_remaining = 50000;
		enemy->act = boss_intelligence;
		enemy->speed = BASE_BLACKHOLE_SPEED;
	}
	else if (enemy->type == et_brazil)
	{
		enemy->act = roam;
		enemy->speed = BASE_SCOOTER_SPEED;
	}
	else
		error_doom("invalid enemy");
}

void    write_enemy_to_file(int fd, t_enemy enemy)
{
	int	i;

	i = -1;
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
	write_str_to_file(fd, enemy.right->userdata);
	write_str_to_file(fd, enemy.left->userdata);
	write_str_to_file(fd, enemy.back->userdata);
	while (++i < 16)
		write_str_to_file(fd, enemy.explosion[i]->userdata);
}

void    read_enemy_from_file(int fd, t_textures *textures, t_enemy *enemy)
{
	int	i;

	i = -1;
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
	find_texture_from_file(fd, textures, &enemy->front);
	find_texture_from_file(fd, textures, &enemy->right);
	find_texture_from_file(fd, textures, &enemy->left);
	find_texture_from_file(fd, textures, &enemy->back);
	init_enemy_from_type(enemy);
	while (++i < 16)
		find_texture_from_file(fd, textures, &(enemy->explosion[i]));
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
	{
		*enemies = NULL;
		return;
	}
	if (!(*enemies = (t_linked_enemies*)malloc(sizeof(t_linked_enemies))))
		error_doom("Couldn't allocate enemies struct");
	(*enemies)->next = NULL;
	read_enemy_from_file(fd, textures, &(*enemies)->item);
	read_enemies_from_file(fd, textures, &(*enemies)->next);
}
