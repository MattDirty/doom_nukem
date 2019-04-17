#ifndef DOOMNUKEM_SOUNDS_H
# define DOOMNUKEM_SOUNDS_H

#include <SDL_mixer.h>

typedef struct	s_sounds
{
    Mix_Music	*lamerde;
    Mix_Chunk	*zap;
    Mix_Chunk	*fu_bitch;
    Mix_Chunk   *xplosion;
    Mix_Chunk   *mip_mep;
    Mix_Chunk   *meeeh;
    Mix_Chunk   *pew;
    Mix_Chunk   *slurp;
    Mix_Chunk   *yeee;
    Mix_Chunk   *mwiiicrkk;
}				t_sounds;

void			read_sounds_from_file(int fd, t_sounds **sounds);
void			write_sounds_to_file(int fd);
void			free_sounds(t_sounds *sounds);

#endif
