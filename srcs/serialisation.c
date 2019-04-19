#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "libft.h"
#include "doom.h"
#include "serialisation.h"

void    check_if_file_is_valid(int *fd, char *filename)
{
    struct stat st;
    struct stat st_verif;

    if ((stat(filename, &st)) < 0)
        error_doom("Couldn't find file stats");
    if (st.st_size > 100000000)
        error_doom("This map is too big ! You ain't fooling anyone, "
                   "you dirty creep.");
    if (st.st_size < 1000000)
    	error_doom("Come on, that's way too small for a map file ! Try doing ./"
				"editor real_map_name and stop trying to break stuff ...");
    *fd = open(filename, O_RDONLY);
    if (*fd <= 0)
    	error_doom("Couldn't open file");
    read(*fd, &st_verif.st_size, sizeof(st_verif.st_size));
    if (st_verif.st_size != st.st_size)
        error_doom("It seems your map has been corrupted. That's naughty!");
}

void	read_file(char *filename, t_env *e)
{
    int fd;

	check_if_file_is_valid(&fd, filename);
    read_fonts_from_file(fd, &e->fonts);
    read_sounds_from_file(fd, &e->sounds);
    read_textures_from_file(fd, &e->textures);
    read_map_from_file(fd, e->textures, &e->map);
    close(fd);
}

void	read_file_editor(char *filename, t_read_data *e)
{
    int fd;

	check_if_file_is_valid(&fd, filename);
    read_fonts_from_file(fd, e->fonts);
    read_sounds_from_file(fd, e->sounds);
    read_textures_from_file(fd, e->textures);
    read_map_from_file(fd, *e->textures, e->map);
	close(fd);
}

void    write_file_protections(int fd, char *filename)
{
    struct stat st;

    if ((stat(filename, &st)) < 0)
        error_doom("Wow, that really shouldn't happen. It seems the map doesn't"
                   "exist ...");
    write(fd, &st.st_size, sizeof(st.st_size));
}

void	write_file(char *filename, t_textures *textures, t_map *map)
{
    int fd;

    fd = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (fd <= 0)
        error_doom("couldn't open file");
	write_file_protections(fd, filename);
    write_fonts_to_file(fd);
    write_sounds_to_file(fd);
    write_textures_to_file(fd, textures);
    write_map_to_file(fd, map);
    close(fd);
    if ((fd = open(filename, O_WRONLY)) <= 0)
        error_doom("There was a problem while reopening the file.");
    write_file_protections(fd, filename);
    close(fd);
}

void	read_str_from_file(int fd, char **name)
{
    char			*c;
    char			*new_name;

    c = ft_strnew(1);
    *name = ft_strnew(1);
    while (1)
    {
        if (read(fd, c, sizeof(char)) <= 0)
            error_doom("couldn't read str in file");
        new_name = ft_strjoin(*name, c);
        free(*name);
        *name = new_name;
        if (!*c)
        {
            free(c);
            return;
        }
    }
}

void	write_str_to_file(int fd, char *name)
{
    char			*c;
    int				i;

    if (!name)
        error_doom("can't write null str");
    i = 0;
    while (1)
    {
        c = name + i++;
        write(fd, c, sizeof(char));
        if (!*c)
            return;
    }
}

void	copy_file_in_file(int fd, char *name)
{
    int				read_bytes;
    int 			name_fd;
    char			*buffer;
    struct stat		statbuf;
    int				size;

    if ((name_fd = open(name, O_RDONLY)) < 0)
		error_doom("couldn't open other file");
    if (fstat(name_fd, &statbuf) < 0)
        error_doom("couldn't find file stats");
    size = statbuf.st_size;
    if (write(fd, &size, sizeof(size)) <= 0)
        error_doom("couldn't write file size");
    if (!(buffer = malloc(1024)))
        error_doom("couln't allocate buffer");
    while (1)
    {
        read_bytes = read(name_fd, buffer, 1024);
        if (read_bytes < 0)
            error_doom("error while copying from file");
        if (write(fd, buffer, read_bytes) != read_bytes)
            error_doom("error while copying to file");
        if (read_bytes < 1024)
            break;
    }
    free(buffer);
    close(name_fd);
}

void	create_tmp_file_from_file(int fd, char *name)
{
    int 			tmp_fd;
    int				read_bytes;
    int				bytes_to_read;
    char			*buffer;

    tmp_fd = open(name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (tmp_fd <= 0)
        error_doom("mabite couldn't open file");
    if (read(fd, &bytes_to_read, sizeof(bytes_to_read)) <= 0)
        error_doom("couldn't read bytes_to_read");
    if (!(buffer = malloc(bytes_to_read)))
        error_doom("couldn't malloc buffer");
    read_bytes = read(fd, buffer, bytes_to_read);
    if (read_bytes <= 0)
        error_doom("rip");
    if (write(tmp_fd, buffer, read_bytes) != bytes_to_read)
        error_doom("oh no");
    free(buffer);
    close(tmp_fd);
}
