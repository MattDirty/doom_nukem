/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_enemies.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 04:27:29 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/19 04:27:32 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "enemies.h"
#include "doom.h"

void				load_explosions(t_textures *textures, t_enemy *new_enemy)
{
	find_texture_by_name(textures, "textures/explosions/explosion_1.bmp",
			&new_enemy->explosion[0]);
	find_texture_by_name(textures, "textures/explosions/explosion_2.bmp",
			&new_enemy->explosion[1]);
	find_texture_by_name(textures, "textures/explosions/explosion_3.bmp",
			&new_enemy->explosion[2]);
	find_texture_by_name(textures, "textures/explosions/explosion_4.bmp",
			&new_enemy->explosion[3]);
	find_texture_by_name(textures, "textures/explosions/explosion_5.bmp",
			&new_enemy->explosion[4]);
	find_texture_by_name(textures, "textures/explosions/explosion_6.bmp",
			&new_enemy->explosion[5]);
	find_texture_by_name(textures, "textures/explosions/explosion_7.bmp",
			&new_enemy->explosion[6]);
	find_texture_by_name(textures, "textures/explosions/explosion_8.bmp",
			&new_enemy->explosion[7]);
	find_texture_by_name(textures, "textures/explosions/explosion_9.bmp",
			&new_enemy->explosion[8]);
	find_texture_by_name(textures, "textures/explosions/explosion_10.bmp",
			&new_enemy->explosion[9]);
	find_texture_by_name(textures, "textures/explosions/explosion_11.bmp",
			&new_enemy->explosion[10]);
	find_texture_by_name(textures, "textures/explosions/explosion_12.bmp",
			&new_enemy->explosion[11]);
}

void				load_explosions2(t_textures *textures, t_enemy *new_enemy)
{
	find_texture_by_name(textures, "textures/explosions/explosion_13.bmp",
			&new_enemy->explosion[12]);
	find_texture_by_name(textures, "textures/explosions/explosion_14.bmp",
			&new_enemy->explosion[13]);
	find_texture_by_name(textures, "textures/explosions/explosion_15.bmp",
			&new_enemy->explosion[14]);
	find_texture_by_name(textures, "textures/explosions/explosion_16.bmp",
			&new_enemy->explosion[15]);
}

t_enemy				create_default_enemy(t_textures *textures)
{
	t_enemy	new_enemy;

	if (!(new_enemy.object = (t_object *)malloc(sizeof(t_object))))
		error_doom("Couldn't allocate object in enemy");
	*new_enemy.object = create_default_object(textures);
	new_enemy.life_remaining = 100;
	new_enemy.death_duration = 1700;
	new_enemy.time_in_death = -1;
	new_enemy.to_destroy = e_false;
	new_enemy.heading = (t_vector){1, 0};
	find_texture_by_name(textures, "textures/sprites/enemy_front.bmp",
			&new_enemy.front);
	find_texture_by_name(textures, "textures/sprites/enemy_left.bmp",
			&new_enemy.left);
	find_texture_by_name(textures, "textures/sprites/enemy_right.bmp",
			&new_enemy.right);
	find_texture_by_name(textures, "textures/sprites/enemy_back.bmp",
			&new_enemy.back);
	new_enemy.type = et_brazil;
	new_enemy.speed = 0;
	load_explosions(textures, &new_enemy);
	load_explosions2(textures, &new_enemy);
	return (new_enemy);
}

int					count_enemies(t_linked_enemies *enemies)
{
	int	i;

	i = 0;
	while (enemies)
	{
		enemies = enemies->next;
		i++;
	}
	return (i);
}

t_linked_enemies	*add_new_enemy_to_sector_at_pos(t_sector *sector,
		t_coords pos, t_textures *textures)
{
	t_linked_enemies	*new_enemy;

	if (count_enemies(sector->enemies) > 208)
		return (NULL);
	if (!(new_enemy = (t_linked_enemies *)malloc(sizeof(t_linked_enemies))))
		error_doom("couldn't allocate new enemy");
	new_enemy->next = NULL;
	new_enemy->item = create_default_enemy(textures);
	new_enemy->item.object->x = pos.x;
	new_enemy->item.object->y = pos.y;
	new_enemy->item.object->sprite = new_enemy->item.front;
	add_enemy(&sector->enemies, new_enemy);
	return (new_enemy);
}
