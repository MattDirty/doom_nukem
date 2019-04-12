#ifndef DOOMNUKEM_SERIALISATION_H
# define DOOMNUKEM_SERIALISATION_H
# include <unistd.h>

# include "textures.h"
# include "map.h"

void	read_file(char *filename, t_textures **textures, t_map **map);
void	write_file(char *filename, t_textures *textures, t_map *map);

void	read_str_from_file(int fd, char **name);
void	write_str_to_file(int fd, char *name);

void	copy_file_in_file(int fd, char *name);
void	create_tmp_file_from_file(int fd, char *name);

#endif
