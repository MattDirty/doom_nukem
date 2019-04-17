#include <unistd.h>
#include "sounds.h"
#include "doom.h"
#include "serialisation.h"

void    delete_sound_tmp_files(void)
{
    if (unlink("roflolilolmao_tmp_lamerde.wav") < 0)
        error_doom("Couldn't delete tmp_lamerde.wav");
    if (unlink("roflolilolmao_tmp_zap.wav") < 0)
        error_doom("Couldn't delete tmp_zap.wav");
    if (unlink("roflolilolmao_tmp_fu_bitch.wav") < 0)
        error_doom("Couldn't delete tmp_fu_bitch.wav");
    if (unlink("roflolilolmao_tmp_xplosion.wav") < 0)
        error_doom("Couldn't delete xplosion.wav");
}

void			read_sounds_from_file(int fd, t_sounds **sounds)
{
    if (!(*sounds = (t_sounds*)malloc(sizeof(t_sounds))))
        error_doom("cannot alloc sounds");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_lamerde.wav");
    (*sounds)->lamerde = Mix_LoadMUS("roflolilolmao_tmp_lamerde.wav");
    if ((*sounds)->lamerde == NULL)
        error_doom("error: couldn't load lamerde");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_zap.wav");
    (*sounds)->zap = Mix_LoadWAV("roflolilolmao_tmp_zap.wav");
    if ((*sounds)->zap == NULL)
        error_doom("error: couldn't load zap");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_fu_bitch.wav");
    (*sounds)->fu_bitch = Mix_LoadWAV("roflolilolmao_tmp_fu_bitch.wav");
    if ((*sounds)->fu_bitch == NULL)
        error_doom("error: couldn't load fu_bitch");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_xplosion.wav");
    (*sounds)->xplosion = Mix_LoadWAV("roflolilolmao_tmp_xplosion.wav");
    if ((*sounds)->xplosion == NULL)
        error_doom("error: couldn't load xplosion");
    delete_sound_tmp_files();
}

void			write_sounds_to_file(int fd)
{
    copy_file_in_file(fd, "sounds/lamerde.wav");
    copy_file_in_file(fd, "sounds/zap.wav");
    copy_file_in_file(fd, "sounds/fu_bitch.wav");
//    copy_file_in_file(fd, "sounds/meeeh.wav");
//    copy_file_in_file(fd, "sounds/mip_mep.wav");
//    copy_file_in_file(fd, "sounds/mwiiiiicrkkkkkkkkkkkkkkkkkkkkkkkkkkkk.wav");
//    copy_file_in_file(fd, "sounds/pew_crk_crk.wav");
//    copy_file_in_file(fd, "sounds/slurp_vrrrr_krrkrkrkrkrkr.wav");
    copy_file_in_file(fd, "sounds/xplosion.wav");
//    copy_file_in_file(fd, "sounds/yeee.wav");
}

void			free_sounds(t_sounds *sounds)
{
    Mix_FreeMusic(sounds->lamerde);
    Mix_FreeChunk(sounds->zap);
    Mix_FreeChunk(sounds->fu_bitch);
    Mix_FreeChunk(sounds->xplosion);
    free(sounds);
}
