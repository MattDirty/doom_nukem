#include <unistd.h>
#include "fonts.h"
#include "doom.h"
#include "serialisation.h"

void    delete_tmp_files(void)
{
    if (unlink("roflolilolmao_tmp_h.ttf") < 0)
        error_doom("Couldn't delete tmp_h.ttf");
    if (unlink("roflolilolmao_tmp_s.ttf") < 0)
        error_doom("Couldn't delete tmp_s.ttf");
    if (unlink("roflolilolmao_tmp_a.ttf") < 0)
        error_doom("Couldn't delete tmp_a.ttf");
}

void			read_fonts_from_file(int fd, t_fonts **fonts)
{
    if (!(*fonts = (t_fonts*)malloc(sizeof(t_fonts))))
        error_doom("cannot alloc fonts");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_h.ttf");
    (*fonts)->horrendo120 = TTF_OpenFont("roflolilolmao_tmp_h.ttf", 120);
    if ((*fonts)->horrendo120 == NULL)
        error_doom("error: couldn't load horrendo120");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_s.ttf");
    (*fonts)->sixty20 = TTF_OpenFont("roflolilolmao_tmp_s.ttf", 20);
    if ((*fonts)->sixty20 == NULL)
        error_doom("error: couldn't load sixty20");
    (*fonts)->sixty40 = TTF_OpenFont("roflolilolmao_tmp_s.ttf", 40);
    if ((*fonts)->sixty40 == NULL)
        error_doom("error: couldn't load sixty40");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_a.ttf");
    (*fonts)->amazdoom40 = TTF_OpenFont("roflolilolmao_tmp_a.ttf", 40);
    if ((*fonts)->amazdoom40 == NULL)
        error_doom("error: couldn't load amazdoom40");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_v.ttf");
    (*fonts)->vcr20 = TTF_OpenFont("roflolilolmao_tmp_v.ttf", 20);
    if ((*fonts)->vcr20 == NULL)
        error_doom("error: couldn't load vcr20");
    (*fonts)->vcr40 = TTF_OpenFont("roflolilolmao_tmp_v.ttf", 40);
    if ((*fonts)->vcr40 == NULL)
        error_doom("error: couldn't load vcr20");
    delete_tmp_files();
}

void			write_fonts_to_file(int fd)
{
    copy_file_in_file(fd, "fonts/horrendo.ttf");
    copy_file_in_file(fd, "fonts/sixty.ttf");
    copy_file_in_file(fd, "fonts/amazdoom.ttf");
    copy_file_in_file(fd, "fonts/vcr_mono.ttf");
}

void			free_fonts(t_fonts *fonts)
{
    TTF_CloseFont(fonts->horrendo120);
    TTF_CloseFont(fonts->sixty20);
    TTF_CloseFont(fonts->sixty40);
    TTF_CloseFont(fonts->amazdoom40);
    TTF_CloseFont(fonts->vcr20);
    TTF_CloseFont(fonts->vcr40);
    free(fonts);
}
