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
    if (unlink("roflolilolmao_tmp_mwiiicrkk.wav") < 0)
        error_doom("Couldn't delete mwiiicrkk.wav");
    if (unlink("roflolilolmao_tmp_mip_mep.wav") < 0)
        error_doom("Couldn't delete mip_mep.wav");
    if (unlink("roflolilolmao_tmp_meeeh.wav") < 0)
        error_doom("Couldn't delete meeeh.wav");
    if (unlink("roflolilolmao_tmp_pew_crk_crk.wav") < 0)
        error_doom("Couldn't delete pew_crk_crk.wav");
    if (unlink("roflolilolmao_tmp_slurp_vrrrr_krrkrkrkrkrkr.wav") < 0)
        error_doom("Couldn't delete slurp.wav");
    if (unlink("roflolilolmao_tmp_yeee.wav") < 0)
        error_doom("Couldn't delete yeee.wav");
}

void			read_sounds_from_file(int fd, t_sounds **sounds)
{
    if (!(*sounds = (t_sounds*)malloc(sizeof(t_sounds))))
        error_doom("cannot alloc sounds");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_lamerde.wav");
    if (!((*sounds)->lamerde = Mix_LoadMUS("roflolilolmao_tmp_lamerde.wav")))
        error_doom("error: couldn't load lamerde");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_zap.wav");
    if (!((*sounds)->zap = Mix_LoadWAV("roflolilolmao_tmp_zap.wav")))
        error_doom("error: couldn't load zap");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_fu_bitch.wav");
    if (!((*sounds)->fu_bitch = Mix_LoadWAV("roflolilolmao_tmp_fu_bitch.wav")))
        error_doom("error: couldn't load fu_bitch");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_xplosion.wav");
    if (!((*sounds)->xplosion = Mix_LoadWAV("roflolilolmao_tmp_xplosion.wav")))
        error_doom("error: couldn't load xplosion");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_mwiiicrkk.wav");
    if (!((*sounds)->mwiiicrkk = Mix_LoadWAV("roflolilolmao_tmp_mwiiicrkk.wav")))
        error_doom("error: couldn't load mwiiicrkk");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_mip_mep.wav");
    if (!((*sounds)->mip_mep = Mix_LoadWAV("roflolilolmao_tmp_mip_mep.wav")))
        error_doom("error: couldn't load mip_mep");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_meeeh.wav");
    if (!((*sounds)->meeeh = Mix_LoadWAV("roflolilolmao_tmp_meeeh.wav")))
        error_doom("error: couldn't load meeeh");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_pew_crk_crk.wav");
    if (!((*sounds)->pew = Mix_LoadWAV("roflolilolmao_tmp_pew_crk_crk.wav")))
        error_doom("error: couldn't load pew_crk_crk");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_slurp_vrrrr_krrkrkrkrkrkr.wav");
    if (!((*sounds)->slurp = Mix_LoadWAV("roflolilolmao_tmp_slurp_vrrrr_krrkrkrkrkrkr.wav")))
        error_doom("error: couldn't load slurp");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_yeee.wav");
    if (!((*sounds)->yeee = Mix_LoadWAV("roflolilolmao_tmp_yeee.wav")))
        error_doom("error: couldn't load yeee");
    delete_sound_tmp_files();
}

void			write_sounds_to_file(int fd)
{
    copy_file_in_file(fd, "sounds/lamerde.wav");
    copy_file_in_file(fd, "sounds/zap.wav");
    copy_file_in_file(fd, "sounds/fu_bitch.wav");
    copy_file_in_file(fd, "sounds/xplosion.wav");
    copy_file_in_file(fd, "sounds/mwiiicrkk.wav");
    copy_file_in_file(fd, "sounds/mip_mep.wav");
    copy_file_in_file(fd, "sounds/meeeh.wav");
    copy_file_in_file(fd, "sounds/pew_crk_crk.wav");
    copy_file_in_file(fd, "sounds/slurp_vrrrr_krrkrkrkrkrkr.wav");
    copy_file_in_file(fd, "sounds/yeee.wav");
}

void			free_sounds(t_sounds *sounds)
{
    Mix_FreeMusic(sounds->lamerde);
    Mix_FreeChunk(sounds->zap);
    Mix_FreeChunk(sounds->fu_bitch);
    Mix_FreeChunk(sounds->xplosion);
    Mix_FreeChunk(sounds->mwiiicrkk);
    Mix_FreeChunk(sounds->mip_mep);
    Mix_FreeChunk(sounds->meeeh);
    Mix_FreeChunk(sounds->pew);
    Mix_FreeChunk(sounds->slurp);
    Mix_FreeChunk(sounds->yeee);
    free(sounds);
}
