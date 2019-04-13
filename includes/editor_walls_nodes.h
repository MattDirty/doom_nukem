#ifndef EDITOR_WALLS_NODES_H
# define EDITOR_WALLS_NODES_H

#include "walls.h"

typedef struct 	s_wall_node
{
	t_wall		*wall;
	int			target_xy;
}				t_wall_node;

typedef struct	s_wall_nodes
{
	t_wall_node			*item;
	struct s_wall_nodes	*next;
}				t_wall_nodes;

void            deal_with_clicked_node(t_linked_walls *linked, t_coords point);

#endif
