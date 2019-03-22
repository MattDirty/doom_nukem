#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "default.h"
#include "doom.h"
#include "libft.h"
#include "config.h"

t_config    load_default_config()
{
    t_config    config;

    config.win_w = WIN_W;
    config.win_h = WIN_H;
    config.half_w = HALF_W;
    config.half_h = HALF_H;
    config.ratio = RATIO;
    config.fullscreen = FULLSCREEN;
    config.fov = FOV;
    config.half_fov = HALF_FOV;
    config.fps_max = FPS_MAX;
    config.mouse_sensi = MOUSE_SENSI;
    config.tan_half_fov = TAN_HALF_FOV;
    config.ratio = RATIO;
    return (config);
}

static int  extract_int_if_line_is_valid(int fd)
{
    char    *line;

    if (get_next_line_from_char(fd, &line, '\n') > 0
            && (line = ft_strchr(line, ':')) != NULL)
        return (ft_atoi(line + 1));
    return (0);
}

t_config    load_ini(int fd)
{
    t_config    config;

    config.win_w = extract_int_if_line_is_valid(fd);
    config.win_h = extract_int_if_line_is_valid(fd);
    config.fullscreen = extract_int_if_line_is_valid(fd);
    config.fov = extract_int_if_line_is_valid(fd);
    config.fps_max = extract_int_if_line_is_valid(fd);
    config.mouse_sensi = extract_int_if_line_is_valid(fd);
    if (config.win_w && config.win_h
        && config.fov && config.fps_max && config.mouse_sensi)
    {
    	config.mouse_sensi /= 1000000;
        config.half_w = config.win_w / 2.0;
        config.half_h = config.win_h / 2.0;
        config.half_fov = config.fov / 2.0;
        config.tan_half_fov = tan(ft_degtorad(config.half_fov));
        config.ratio = (config.half_w / config.tan_half_fov);
    }
    else
    {
        config = load_default_config();
        ft_putendl("There was an issue with config.ini so"
                   " default config has been loaded.");
    }
    return (config);
}

void        create_config_file(t_config *config)
{
    int     fd;

    if ((fd = open(CONFIG_PATH, O_RDWR | O_CREAT, 0777)) < 0)
        error_doom("couldn't create config file.");
    ft_putendl_fd(
            ft_strjoin("resolution x:", ft_itoa(config->win_w)), fd);
    ft_putendl_fd(
            ft_strjoin("resolution y:",ft_itoa(config->win_h)), fd);
    ft_putendl_fd(
            ft_strjoin("fullscreen:", ft_itoa((int)config->fullscreen)), fd);
    ft_putendl_fd(
            ft_strjoin("FOV:",ft_itoa((int)round(config->fov))), fd);
    ft_putendl_fd(
            ft_strjoin("FPS :",ft_itoa(config->fps_max)), fd);
    ft_putendl_fd(
            ft_strjoin("mouse sensitivity:",
                    ft_itoa((int)round(config->mouse_sensi * 1000000))), fd);
    close(fd);
}

t_config    load_config()
{
    int         fd;
    t_config    config;

    if ((fd = open(CONFIG_PATH, O_RDWR)) < 0)
    {
        config = load_default_config();
        create_config_file(&config);
    }
    else
        config = load_ini(fd);
    close (fd);
    return (config);
}