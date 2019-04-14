#include "editor_mouse_clicks.h"

void            deal_with_clicked_player(t_editor *ed, t_coords *spawn)
{
	ed->selected_player = spawn;
}

void			deal_with_clicked_enemy(t_editor *ed, t_enemy *enemy)
{
	ed->selected_enemy = enemy;
}