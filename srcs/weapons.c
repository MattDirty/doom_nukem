#include "doom.h"

t_weapon    load_weapon(SDL_Surface *texture)
{
    t_weapon    weapon;

    weapon.sprite = texture;
    weapon.ammo = 0;
    weapon.main = NULL;
    weapon.secondary = NULL;
    weapon.usable = t_true;
    return (weapon);
}

t_weapons   allocate_weapons()
{
    t_weapons   weapons;
    SDL_Surface **textures;
    int         i;

    weapons.size = 1; // todo: read shit
    weapons.current = 0;
    if (!(weapons.list = (t_weapon *)malloc(sizeof(t_weapon) * weapons.size)))
        error_doom("error: cannot allocate memory for struct weapons");
    if (!(textures = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * weapons.size)))
        error_doom("error: cannot allocate memory for weapons textures");
    i = 0;
    while (i < weapons.size)
    {
        if (!(textures[i] = SDL_LoadBMP("dwa.bmp"))) //todo : texture loader
            error_doom("there was an error while loading the BMP (weapon)");
        weapons.list[i] = load_weapon(textures[i]); //todo : weapon mod
        i++;
    }
    return (weapons);
}