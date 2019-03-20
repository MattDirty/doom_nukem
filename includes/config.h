#ifndef DOOMNUKEM_CONFIG_H
# define DOOMNUKEM_CONFIG_H

# include "e_bool.h"

typedef struct  s_config
{
    Uint32      win_w;
    Uint32      win_h;
    double      half_w;
    double      half_h;
    double      ratio;

    enum e_bool fullscreen;

    double      fov;
    double      half_fov;
    double      tan_half_fov;

    int         fps_max;

    double      mouse_sensi;
}               t_config;

t_config    load_config();

#endif
