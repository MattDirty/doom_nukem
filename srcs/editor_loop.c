#include "editor.h"
#include "editor_move_stuff.h"

int		event_editor(t_editor *ed)
{
	double      x;
	double      y;
	SDL_Event	ev;

	x = 0;
	y = 0;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_MOUSEMOTION)
		{
			x += ev.motion.xrel;
			y += ev.motion.yrel;
		}
		if (ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE || ev.type == SDL_QUIT)
			quit_editor(ed);
		if (ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT)
			mousedown_action(ed, ev.button.x, ev.button.y);
		if (ev.type == SDL_MOUSEBUTTONUP && ev.button.button == SDL_BUTTON_LEFT)
			mouseup_action(ed, ev.button.x, ev.button.y);
	}

	if (ed->dragged.nodes)
		move_walls_nodes(ed->dragged.nodes, x, y);
	else if (ed->dragged.p_spawn)
		move_player_spawn(ed->dragged.p_spawn, x, y);
	else if (ed->dragged.object)
		move_object(ed->dragged.object, x, y);
	return (1);
}

void	reframe_editor(t_editor *ed)
{
	SDL_Texture		*texture;

	draw_background(ed);
	draw_editor(ed);
	draw_panel(ed);
	SDL_RenderClear(ed->sdl.renderer);
	if (!(texture = SDL_CreateTextureFromSurface(ed->sdl.renderer, ed->sdl.surface)))
		error_doom("Could not create texture");
	SDL_RenderCopy(ed->sdl.renderer, texture, 0, 0);
	SDL_RenderPresent(ed->sdl.renderer);
	SDL_DestroyTexture(texture);
}

void	editor_loop(t_editor *ed)
{
	reframe_editor(ed);
	ed->buttons.count = 1;
	while (1)
	{
		reframe_editor(ed);
		event_editor(ed);
	}
}