#include "weapon.h"
#include "doom.h"

t_weapon    load_gun(t_map *map)
{
    t_weapon    weapon;
    Uint32 i;

    weapon.sprites_count = 3;
    if (!(weapon.sprites = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * weapon.sprites_count)))
        error_doom("Couldn't malloc gun.sprites");
    i = 0;
    while (i < weapon.sprites_count)
    {
        weapon.sprites[i] = map->gun_sprites[i];
        i++;
    }
    weapon.ammo = 10;
    weapon.main = NULL;
    weapon.usable = t_true;
    reset_animation(&weapon.animation);
    weapon.main = melee_primary;
    weapon.main_cooldown = 2000;
    weapon.main_ready = t_true;
    if (!(weapon.main_sound = Mix_LoadWAV("sounds/fu_bitch.wav")))
        error_doom("Can't load weapon sound ...");
    return (weapon);
}
