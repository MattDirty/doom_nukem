#ifndef EDITOR_PANEL_H
# define EDITOR_PANEL_H

# define PANEL_PADDING_LEFT 20
# define PANEL_MINIATURE_MAX_W 80
# define PANEL_MINIATURE_MAX_H 80
# define PANEL_W EDITOR_W / 3
# define PANEL_H EDITOR_H
# define SAVE_BORDER 0xFF0c5606
# define SAVE_CENTER 0xFF11d102
# define PANEL_BACKGROUND 0xFF073784


typedef struct          s_panel
{
    SDL_Surface     	*surface;
    t_textures			skies;
    t_textures			walls;
    t_textures			flats;
    t_textures			sprites;
    t_textures			wall_objects;
}						t_panel;

void		editor_draw_panel_map(t_editor *ed);
void        write_panel_state(t_editor *ed, char *state_str);
void		draw_sprites_section(
		t_editor *ed, t_textures *sprites, char *title_str, int *y);
void		editor_draw_panel_walls(t_editor *ed);
void        editor_draw_panel_sprites(t_editor *ed);
void        editor_draw_panel_sector(t_editor *ed);

#endif
