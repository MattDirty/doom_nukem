#include <stdio.h>

#include "SDL.h"
#include "editor.h"
#include "doom.h"
#include "map.h"
#include "serialisation.h"
#include "libft.h"

t_map		*create_map(t_textures *textures)
{
	int			i;
	int			j;
	t_walls*	walls;
	t_map		*map;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		error_doom("error: cannot allocate memory for struct map");

	if (!(map->sectors = (t_sectors*)malloc(sizeof(t_sectors))))
		error_doom("t_sectors");

	map->sectors->count = 3;
	if (!(map->sectors->items =
				(t_sector*)malloc(map->sectors->count * sizeof(t_sector))))
		error_doom("Can't allocate sectors");

	i = 0;
	while (i < map->sectors->count)
	{
		if (!(map->sectors->items[i].walls = (t_walls*)malloc(sizeof(t_walls))))
			error_doom("t_walls");

        find_texture_by_name(textures, "textures/flats/grass.bmp", &map->sectors->items[i].floor);
        find_texture_by_name(textures, "textures/flats/dirt.bmp", &map->sectors->items[i].ceil);
        map->sectors->items[i].open_sky = t_false;
        map->sectors->items[2].open_sky = t_true;
        map->sectors->items[i].objects = (t_objects*)malloc(sizeof(t_objects));
        map->sectors->items[i].objects->count = 0;
        map->sectors->items[i].enemies = (t_enemies*)malloc(sizeof(t_enemies));
        map->sectors->items[i].enemies->count = 0;
        map->sectors->items[i].objects->items = NULL;
       // if (i == 0)
        //{
            map->sectors->items[i].objects->count = 3;
            map->sectors->items[i].objects->items = (t_object*)malloc(
                    sizeof(t_object) * map->sectors->items[i].objects->count);
            map->sectors->items[i].objects->items[0].x = 1;
            map->sectors->items[i].objects->items[0].y = i * 4 + 2;;
            map->sectors->items[i].objects->items[0].z = 0;
            map->sectors->items[i].objects->items[0].horizontal_size = 0.25;
            map->sectors->items[i].objects->items[0].vertical_size = 0.25;
            find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[0].sprite);
        //}
        map->sectors->items[i].objects->items[1].x = 2;
        map->sectors->items[i].objects->items[1].y = i * 4 + 2;
        map->sectors->items[i].objects->items[1].z = 0;
        map->sectors->items[i].objects->items[1].horizontal_size = 0.25;
        map->sectors->items[i].objects->items[1].vertical_size = 0.5;
        map->sectors->items[i].objects->items[2].x = 3;
        map->sectors->items[i].objects->items[2].y = i * 4 + 2;
        map->sectors->items[i].objects->items[2].z = 0;
        map->sectors->items[i].objects->items[2].horizontal_size = 0.25;
        map->sectors->items[i].objects->items[2].vertical_size = 1;
        find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[1].sprite);
        find_texture_by_name(textures, "textures/sprites/voilaunefleur.bmp", &map->sectors->items[i].objects->items[2].sprite);

        map->sectors->items[i].enemies = (t_enemies*)malloc(sizeof(t_enemies));
        map->sectors->items[i].enemies->count = 1;
        if (!(map->sectors->items[i].enemies->items = (t_enemy*)malloc(
                sizeof(t_enemy) * map->sectors->items[i].enemies->count)))
            error_doom("Couldn't allocate enemies\n");

        if (!(map->sectors->items[i].enemies->items[0].object = (t_object *)
                malloc(sizeof(t_object))))
            error_doom("couldn't allocate enemies objects");
        map->sectors->items[i].enemies->items[0].object->x = 1;
        map->sectors->items[i].enemies->items[0].object->y = i * 4 + 1;;
        map->sectors->items[i].enemies->items[0].object->z = 0;
        map->sectors->items[i].enemies->items[0].object->horizontal_size = 1;
        map->sectors->items[i].enemies->items[0].object->vertical_size = 1;
        map->sectors->items[i].enemies->items[0].hp = 100;
        map->sectors->items[i].enemies->items[0].heading = 0;
        if (i == 1)
            map->sectors->items[i].enemies->items[0].heading = ft_degtorad(90);
        if (i == 2)
            map->sectors->items[i].enemies->items[0].heading = ft_degtorad(180);
        find_texture_by_name(textures,"textures/sprites/enemy_front.bmp", &map->sectors->items[i].enemies->items[0].front);
        map->sectors->items[i].enemies->items[0].object->sprite =
                map->sectors->items[i].enemies->items[0].front;
        find_texture_by_name(textures,"textures/sprites/enemy_side.bmp", &map->sectors->items[i].enemies->items[0].side);

		walls = map->sectors->items[i].walls;
		find_texture_by_name(
				textures,
				"textures/walls/stones.bmp",
				&map->sectors->items[1].floor);
		find_texture_by_name(
				textures,
				"textures/flats/dirt.bmp",
				&map->sectors->items[2].floor);
		walls->count = 4;

		if (!(walls->items = (t_wall**)malloc(walls->count * sizeof(t_wall*))))
			error_doom("Can't allocate walls");

        j = 0;
        while (j < walls->count)
            if (!(walls->items[j++] = (t_wall*)malloc(sizeof(t_wall))))
                error_doom("Can't allocate wall");

		walls->items[0]->segment = create_segment(0, 0 + i * 4, 0, 4 + i * 4);
		walls->items[1]->segment = create_segment(0, 4 + i * 4, 4, 4 + i * 4);
		walls->items[2]->segment = create_segment(4, 4 + i * 4, 4, 0 + i * 4);
		walls->items[3]->segment = create_segment(4, 0 + i * 4, 0, 0 + i * 4);

		j = 0;
		while (j < walls->count)
		{
		    walls->items[j]->type = e_wall;
		    if (i == 1)
                find_texture_by_name(textures, "textures/walls/stones.bmp", &walls->items[j]->pointer.texture);
		    else
                find_texture_by_name(textures, "textures/walls/brickwall2.bmp", &walls->items[j]->pointer.texture);
			j++;
		}
		if (i == 0)
		{
			walls->items[1]->type = e_portal;
			walls->items[1]->pointer.sector.sector1 = &map->sectors->items[0];
			walls->items[1]->pointer.sector.sector2 = &map->sectors->items[1];
			map->sectors->items[i].light = 0x32000000;
		}
		else if (i == 1)
        {
			walls->items[1]->type = e_portal;
			walls->items[1]->pointer.sector.sector1 = &map->sectors->items[1];
			walls->items[1]->pointer.sector.sector2 = &map->sectors->items[2];
			free(walls->items[3]);
			walls->items[3] = map->sectors->items[0].walls->items[1];
			map->sectors->items[i].light = 0x64000000;
		}
		else
		{
			free(walls->items[3]);
			walls->items[3] = map->sectors->items[1].walls->items[1];
			map->sectors->items[i].light = 0x96000000;
		}
		i++;
	}
    find_texture_by_name(textures, "textures/skybox/day.bmp", &map->daysky);
    find_texture_by_name(textures, "textures/skybox/night.bmp", &map->nightsky);
    find_texture_by_name(textures, "textures/hud/sun.bmp", &map->hud.sun);
    find_texture_by_name(textures, "textures/hud/moon.bmp", &map->hud.moon);
	find_texture_by_name(textures, "textures/hud/health/ico1.bmp", &map->hud.cross[0]);
	find_texture_by_name(textures, "textures/hud/health/ico2.bmp", &map->hud.cross[1]);
	find_texture_by_name(textures, "textures/hud/health/ico3.bmp", &map->hud.cross[2]);
    find_texture_by_name(textures, "textures/hud/bullet.bmp", &map->hud.bullet);
	find_texture_by_name(textures, "textures/hud/faces/happy.bmp", &map->hud.happy_face);
	find_texture_by_name(textures, "textures/hud/faces/meh.bmp", &map->hud.meh_face);
	find_texture_by_name(textures, "textures/hud/faces/sad.bmp", &map->hud.sad_face);
	find_texture_by_name(textures, "textures/hud/faces/dead.bmp", &map->hud.dead_face);
	find_texture_by_name(textures, "textures/hud/faces/badass.bmp", &map->hud.badass_face);
	find_texture_by_name(textures, "textures/hud/faces/sehr_happy.bmp", &map->hud.sehr_happy_face);
	find_texture_by_name(textures, "textures/hud/faces/hurt.bmp", &map->hud.hurt_face);
    map->daytime = t_true;
	return (map);
}

t_textures	*load_textures(void)
{
    t_textures	*textures;

    if (!(textures = (t_textures*)malloc(sizeof(t_textures))))
        error_doom("could not allocate textures");
    textures->first = NULL;
    add_bitmap_file_to_textures(textures, "textures/weapons/dwa.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/stones.bmp");
    add_bitmap_file_to_textures(textures, "textures/walls/brickwall2.bmp");
    add_bitmap_file_to_textures(textures, "textures/flats/grass.bmp");
    add_bitmap_file_to_textures(textures, "textures/flats/dirt.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/voilaunefleur.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_front.bmp");
    add_bitmap_file_to_textures(textures, "textures/sprites/enemy_side.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/day.bmp");
    add_bitmap_file_to_textures(textures, "textures/skybox/night.bmp");
    add_bitmap_file_to_textures(textures, "textures/hud/sun.bmp");
    add_bitmap_file_to_textures(textures, "textures/hud/moon.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico1.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico2.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/health/ico3.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/bullet.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/happy.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/meh.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/sad.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/dead.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/badass.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/sehr_happy.bmp");
	add_bitmap_file_to_textures(textures, "textures/hud/faces/hurt.bmp");
    return (textures);
}

///////////////////////////////////////////////

void		draw_walls_editor(SDL_Surface *surface, t_walls *walls)
{
	int	i;
	t_segment s2;
	t_segment s;

	i = 0;
	while (i < walls->count)
	{
		s = walls->items[i]->segment;
		s2.x1 = EDITOR_W_H + s.x1 * EDITOR_ZOOM;
		s2.y1 = EDITOR_H_H - s.y1 * EDITOR_ZOOM;
		s2.x2 = EDITOR_W_H + s.x2 * EDITOR_ZOOM;
		s2.y2 = EDITOR_H_H - s.y2 * EDITOR_ZOOM;
		if (walls->items[i]->type == e_wall)
    	    draw_segment(surface, s2, 0xFFFFFFFF);
		else if (walls->items[i]->type == e_portal)
		    draw_segment(surface, s2, 0xFFFF0000);
		i++;
	}
}

void		draw_editor(t_sdl_editor *sdl_ed, t_map *map)
{
	int i;

	i = 0;
	while (i < map->sectors->count)
	{
		draw_walls_editor(sdl_ed->surface, map->sectors->items[i].walls);
		i++;
	}
}

void    init_sdl_editor(Uint32 w, Uint32 h, char *name, t_sdl_editor *sdl_ed)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error_doom("error: cannot run SDL");
    if (!(sdl_ed->window = SDL_CreateWindow(name, 0, 0, w, h, 0)))
        error_doom("Could not create window.");
	SDL_RaiseWindow(sdl_ed->window);
    if (!(sdl_ed->renderer = SDL_CreateRenderer(sdl_ed->window, -1, 0)))
        error_doom("Could not create renderer");
	if (!(sdl_ed->surface = SDL_CreateRGBSurface(0, w, h,
			32, MASK_RED, MASK_GREEN, MASK_BLUE, MASK_ALPHA)))
        error_doom("Could not create surface.");
}

int		event_editor(t_map *map, t_sdl_editor *sdl_ed)
{
	SDL_Event	event;

	(void)map;
	(void)sdl_ed;
	SDL_PollEvent(&event);
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		exit(EXIT_FAILURE);
	return (1);
}

void	reframe_editor(t_map *map, t_sdl_editor *sdl_ed)
{
	SDL_Texture		*texture;
	(void)map;

	draw_editor(sdl_ed, map);
	SDL_RenderClear(sdl_ed->renderer);
	if (!(texture = SDL_CreateTextureFromSurface(sdl_ed->renderer, sdl_ed->surface)))
		error_doom("Could not create texture");
	SDL_RenderCopy(sdl_ed->renderer, texture, 0, 0);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(sdl_ed->renderer);
}

void	gameloop(t_map *map, t_sdl_editor *sdl_ed)
{
	reframe_editor(map, sdl_ed);
	while (1)
	{
		if (event_editor(map, sdl_ed))
			reframe_editor(map, sdl_ed);
	}
}

int		main(void)
{
	t_sdl_editor		sdl_ed;
	t_textures			*textures;
    t_map				*map;

	ft_bzero(&sdl_ed, sizeof(t_sdl_editor));
    textures = load_textures();
    map = create_map(textures);
	write_file("mabite.roflolilolmao", textures, map);

	init_sdl_editor(EDITOR_W, EDITOR_H, "editor", &sdl_ed);

	gameloop(map, &sdl_ed);

	printf("ta mere est une pute\n"); //j'aimerais que la norminette m'engueule.
    return (0);
}
