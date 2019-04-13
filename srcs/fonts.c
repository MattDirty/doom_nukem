#include "fonts.h"
#include "doom.h"
#include "serialisation.h"

void			read_fonts_from_file(int fd, t_fonts **fonts)
{
    if (!(*fonts = (t_fonts*)malloc(sizeof(t_fonts))))
        error_doom("cannot alloc fonts");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_h.ttf");
    (*fonts)->horrendo120 = TTF_OpenFont("roflolilolmao_tmp_h.ttf", 120);
    if ((*fonts)->horrendo120 == NULL)
        error_doom("error: couldn't load horrendo120");
    create_tmp_file_from_file(fd, "roflolilolmao_tmp_s.ttf");
    (*fonts)->sixty20 = TTF_OpenFont("roflolilolmao_tmp_s.ttf", 120);
    if ((*fonts)->sixty20 == NULL)
        error_doom("error: couldn't load sixty20");
    (*fonts)->sixty40 = TTF_OpenFont("roflolilolmao_tmp_s.ttf", 120);
    if ((*fonts)->sixty40 == NULL)
        error_doom("error: couldn't load sixty40");
}

void			write_fonts_to_file(int fd)
{
    copy_file_in_file(fd, "fonts/horrendo.ttf");
    copy_file_in_file(fd, "fonts/sixty.ttf");
}

void			free_fonts(t_fonts *fonts)
{
    TTF_CloseFont(fonts->horrendo120);
    TTF_CloseFont(fonts->sixty20);
    TTF_CloseFont(fonts->sixty40);
    free(fonts);
}
