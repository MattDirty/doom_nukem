#ifndef DOOMNUKEM_SERIALISATION_H
# define DOOMNUKEM_SERIALISATION_H
# include <unistd.h>

# include "textures.h"
# include "map.h"

int	read_file(char *filename, t_textures **textures, t_map **map);
void	write_file(char *filename, t_textures *textures, t_map *map);

int	read_str_from_file(int fd, char **name);
int	write_str_to_file(int fd, char *name);

#endif
