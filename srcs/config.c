#include <fcntl.h>
#include <math.h>
#include <unistd.h>
#include "default.h"
#include "doom.h"
#include "libft.h"
#include "config.h"

void        create_config_file(t_config *config)
{
    int     fd;

    if ((fd = open(CONFIG_PATH, O_WRONLY | O_CREAT)) < 0)
        error_doom("couldn't create config file.");
    ft_putendl_fd(ft_itoa(config->win_w), fd);
    ft_putendl_fd(ft_itoa(config->win_h), fd);
    ft_putendl_fd(ft_itoa((int)config->fullscreen), fd);
    ft_putendl_fd(ft_itoa((int)round(config->fov)), fd);
    ft_putendl_fd(ft_itoa(config->fps_max), fd);
    ft_putendl_fd(ft_itoa((int)round(config->mouse_sensi * 1000000)), fd);
    close(fd);
}

void        load_default_config(t_config *config)
{
    config->win_w = WIN_W;
    config->win_h = WIN_H;
    config->half_w = HALF_W;
    config->half_h = HALF_H;
    config->fullscreen = FULLSCREEN;
    config->fov = FOV;
    config->half_fov = HALF_FOV;
    config->fps_max = FPS_MAX;
    config->mouse_sensi = MOUSE_SENSI;
}

t_config    load_config()
{
    int         fd;
    t_config    config;

    if ((fd = open(CONFIG_PATH, O_RDWR)) < 0)
    {
        load_default_config(&config);
        create_config_file(&config);
    }
    config.fullscreen = t_false;
    return (config);
}