#ifndef EDITOR_WALLS_NODES_H
# define EDITOR_WALLS_NODES_H

#include "walls.h"
#include "editor.h"

typedef struct s_editor t_editor;

typedef struct 	s_wall_node
{
	t_wall		*wall;
	double      *x;
	double      *y;
}				t_wall_node;

typedef struct	s_wall_nodes
{
	t_wall_node			item;
	struct s_wall_nodes	*next;
}				t_wall_nodes;

void            deal_with_clicked_node(
        t_editor *ed, t_linked_walls *linked, t_coords point);
void    move_walls_nodes(t_wall_nodes *nodes, double x, double y);
void    free_walls_nodes(t_wall_nodes *nodes);

#endif
