#ifndef DOOMNUKEM_CONFIG_H
# define DOOMNUKEM_CONFIG_H

# include "e_bool.h"

typedef struct  s_config
{
    int         win_w;
    int         win_h;
    double      half_w;
    double      half_h;

    enum e_bool fullscreen;

    double      fov;
    double      half_fov;

    int         fps_max;

    double      mouse_sensi;
}               t_config;

t_config    load_config();

#endif
