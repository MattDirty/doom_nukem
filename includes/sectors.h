#ifndef SECTORS_H
# define SECTORS_H

# include "textures.h"
# include "walls.h"
# include "objects.h"
# include "enemies.h"

typedef struct s_linked_enemies t_linked_enemies;
typedef struct s_enemy t_enemy;

typedef	struct			s_sector
{
    t_walls			    *walls;
    SDL_Surface         *floor;
    SDL_Surface         *ceil;
    enum e_bool         open_sky;
    Uint32				light;
    t_objects           *objects;
    t_linked_enemies    *enemies;
}						t_sector;

typedef struct			s_sectors
{
    int					count;
    t_sector			 *items;
}						t_sectors;

void		free_sectors(t_sectors *sectors);
void		read_sectors_from_file(
        int fd,
        t_textures *textures,
        t_sectors **sectors);
void		write_sectors_to_file(int fd, t_sectors *sectors);

int		sector_index(t_sectors *sectors, t_sector *sector);
t_sector    *find_wall_sector(t_sectors *sectors, t_wall *wall);
t_sector    *find_object_sector(t_sectors *sectors, t_object *object);
t_sector	*find_enemy_sector(t_sectors *sectors, t_enemy *enemy);
enum e_bool	walls_intersection_in_sector(t_sector *sector);

#endif
