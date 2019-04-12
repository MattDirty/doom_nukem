#include "fonts.h"

void			read_fonts_from_file(int fd, t_fonts **fonts)
{
    TTF_Font	*font;

    if (!(*fonts = (t_fonts*)malloc(sizeof(t_fonts))))
        error_doom("cannot alloc fonts");
    create_tmp_file_from_file(fd, "roflolilolmao.tmp.ducul");
    if (!((*fonts)->horrendo120 = TTF_OpenFont("roflolilolmao.tmp.ducul", 120)))
        error_doom("error: couldn't load horrendo120");
    create_tmp_file_from_file(fd, "roflolilolmao.tmp.ducul");
    if (!((*fonts)->sixty20 = TTF_OpenFont("roflolilolmao.tmp.ducul", 20)))
        error_doom("error: couldn't load sixty20");
    if (!((*fonts)->sixty40 = TTF_OpenFont("roflolilolmao.tmp.ducul", 40)))
        error_doom("error: couldn't load sixty40");
}

void			write_fonts_to_file(int fd)
{
    copy_file_in_file(fd, "fonts/horrendo.ttf");
    copy_file_in_file(fd, "fonts/sixty.ttf");
}
