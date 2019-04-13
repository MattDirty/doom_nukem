#ifndef EDITOR_WALLS_NODES_H
# define EDITOR_WALLS_NODES_H

typedef struct 	s_wall_node
{
	t_wall		wall;
	int			target_xy;
}				t_wall_node;

typedef struct	s_wall_nodes
{
	t_wall_node			*item;
	struct s_wall_nodes	*next;
}				t_wall_nodes;

#endif EDITOR_WALLS_NODES_H
