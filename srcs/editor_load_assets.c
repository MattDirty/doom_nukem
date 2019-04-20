/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_load_assets.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfatton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:23:01 by lfatton           #+#    #+#             */
/*   Updated: 2019/04/20 03:23:03 by lfatton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "editor.h"

t_fonts		*load_fonts(void)
{
	t_fonts	*fonts;

	if (!(fonts = (t_fonts *)malloc(sizeof(t_fonts))))
		error_doom("cannot alloc fonts");
	fonts->horrendo120 = TTF_OpenFont("fonts/horrendo.ttf", 120);
	fonts->sixty20 = TTF_OpenFont("fonts/sixty.ttf", 20);
	fonts->sixty40 = TTF_OpenFont("fonts/sixty.ttf", 40);
	fonts->amazdoom40 = TTF_OpenFont("fonts/amazdoom.ttf", 40);
	fonts->vcr20 = TTF_OpenFont("fonts/vcr_mono.ttf", 20);
	fonts->vcr40 = TTF_OpenFont("fonts/vcr_mono.ttf", 40);
	if (!fonts->horrendo120 || !fonts->sixty20 || !fonts->sixty40
		|| !fonts->amazdoom40 || !fonts->vcr20 || !fonts->vcr40)
		error_doom("Couldn't open fonts");
	return (fonts);
}

t_sounds	*load_sounds(void)
{
	t_sounds	*sounds;

	if (!(sounds = (t_sounds *)malloc(sizeof(t_sounds))))
		error_doom("cannot alloc sounds");
	if (!(sounds->lamerde = Mix_LoadMUS("sounds/lamerde.wav")))
		error_doom("error: cannot load lamerde.wav");
	if (!(sounds->zap = Mix_LoadWAV("sounds/zap.wav")))
		error_doom("error: cannot load zap.wav");
	if (!(sounds->fu_bitch = Mix_LoadWAV("sounds/fu_bitch.wav")))
		error_doom("error: cannot load fu_bitch.wav");
	if (!(sounds->xplosion = Mix_LoadWAV("sounds/xplosion.wav")))
		error_doom("error: cannot load xplosion.wav");
	if (!(sounds->mwiiicrkk = Mix_LoadWAV("sounds/mwiiicrkk.wav")))
		error_doom("error: cannot load mmwiiicrkk.wav");
	if (!(sounds->mip_mep = Mix_LoadWAV("sounds/mip_mep.wav")))
		error_doom("error: cannot load mip_mep.wav");
	if (!(sounds->meeeh = Mix_LoadWAV("sounds/meeeh.wav")))
		error_doom("error: cannot load meeeh.wav");
	if (!(sounds->pew = Mix_LoadWAV("sounds/pew_crk_crk.wav")))
		error_doom("error: cannot load pew.wav");
	if (!(sounds->slurp = Mix_LoadWAV("sounds/slurp_vrrrr_krrkrkrkrkrkr.wav")))
		error_doom("error: cannot load surlp.wav");
	if (!(sounds->yeee = Mix_LoadWAV("sounds/yeee.wav")))
		error_doom("error: cannot load yeee.wav");
	return (sounds);
}

static void	clear_panel(t_panel *panel)
{
	panel->skies.first = NULL;
	panel->walls.first = NULL;
	panel->flats.first = NULL;
	panel->pickables.first = NULL;
	panel->wall_objects.first = NULL;
}

static void	sort_into_lists(char *str, t_panel *panel, t_texture_node *new_node)
{
	if (ft_strstr(str, "/skybox/"))
		add_texture(&panel->skies, new_node);
	else if (ft_strstr(str, "/walls/"))
		add_texture(&panel->walls, new_node);
	else if (ft_strstr(str, "/flats/"))
		add_texture(&panel->flats, new_node);
	else if (ft_strstr(str, "/wall_objects/"))
		add_texture(&panel->wall_objects, new_node);
	else if ((ft_strstr(str, "/gun.bmp") || ft_strstr(str, "/shotgun.bmp")
			|| ft_strstr(str, "/vacuum.bmp")))
		add_texture(&panel->pickables, new_node);
	else
		free(new_node);
}

void		create_sub_lists(t_textures *textures, t_panel *panel)
{
	t_texture_node	*node;
	t_texture_node	*new_node;
	char			*str;

	clear_panel(panel);
	node = textures->first;
	while (node)
	{
		if (!(new_node = (t_texture_node *)malloc(sizeof(t_texture_node))))
			error_doom("Couldn't malloc new node");
		new_node->texture = node->texture;
		new_node->next = NULL;
		str = node->texture->userdata;
		sort_into_lists(str, panel, new_node);
		node = node->next;
	}
}
