# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badhont <badhont@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 17:35:48 by lfatton           #+#    #+#              #
#    Updated: 2019/04/19 20:20:57 by badhont          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, extract, run, redit, debug, editor, norm, git, clean, fclean, re

NAME = doom-nukem

NAME_EDITOR = editor

SRC_PATH = srcs

SRCS_NAMES = collision.c \
			collision2.c \
			segment.c \
			segment2.c \
			rectangle.c \
			player.c \
			serialisation.c \
			serialisation2.c \
			serialisation_enemies.c \
			serialisation_objects.c \
			serialisation_pickables.c \
			serialisation_ui.c \
			walls.c \
			wall_objects.c \
			sectors.c \
			sectors2.c \
			sectors_find_stuff.c \
			map.c \
			levers.c \
			environment.c \
			loop.c \
			events_handler.c \
			game_endings.c \
			fonts.c \
			engine.c \
			engine2.c \
			vertical_motion.c \
			horizontal_motion.c \
			sounds.c \
			render_utils.c \
			bitmaps.c \
			objects.c \
			render.c \
			render_blackhole.c \
			render_draw_pickable.c \
			render_draw_object.c \
			render_flats.c \
			render_on_screen.c \
			render_walls.c \
			enemies_intelligence.c \
			basic_enemies_intelligence.c \
			basic_enemies_intelligence2.c \
			draw_tools.c \
			ui_draw.c \
			ui_elements.c \
			ui_utils.c \
			timer_handler.c \
			time.c \
			weapons.c \
			weapon_draw.c \
			utils.c \
			animation.c \
			melee.c \
			in_which_sector.c \
			in_which_sector_utils.c \
			gun.c \
			shotgun.c \
			vacuum.c \
			skybox.c \
			config.c \
			textures.c \
			textures2.c \
			keyboard.c \
			enemies.c \
			enemies_damage.c \
			vector.c \
			vector2.c \
			walls_rw.c \
			walls_rw2.c \
			walls_transformations.c \
			draw_wall_object.c \
			weapon_ray_fire.c \
			pickables.c

SRC_NAME =	main.c \
			$(SRCS_NAMES)

SRC_EDITOR_NAME = editor.c \
				  editor_load_assets.c \
				  editor_checks.c \
				  editor_check_map.c \
				  editor_loop.c \
				  editor_draw.c \
				  editor_draw2.c \
				  editor_panel.c \
				  editor_panel_map.c \
				  editor_panel_sector.c \
				  editor_panel_wall.c \
				  editor_panel_wall2.c \
				  editor_panel_object.c \
				  editor_panel_object2.c \
				  editor_panel_enemy.c \
				  editor_panel_pickable.c \
				  editor_panel_textures.c \
				  editor_segments.c \
				  editor_panel_buttons.c \
				  editor_mouse_clicks.c \
				  editor_mouse_clicks_utils.c \
				  editor_mouse_clicks_on.c \
				  editor_mouse_clicks_on2.c \
				  editor_mouse_clicks_action.c \
				  editor_add_elements_in_map.c \
				  editor_move_stuff.c \
				  editor_move_stuff2.c \
				  editor_states.c \
				  editor_enemies.c \
				  editor_objects.c \
				  editor_pickables.c \
				  editor_walls_nodes.c \
				  $(SRCS_NAMES)

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

SRCS_EDITOR = $(addprefix $(SRC_PATH)/,$(SRC_EDITOR_NAME))

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_EDITOR_NAME = $(SRC_EDITOR_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

OBJS_EDITOR = $(addprefix $(OBJ_PATH)/,$(OBJ_EDITOR_NAME))

INCL = includes

LIBFT_INCL_PATH = ./libft/includes

LDLIBFT = -L ./libft -lft -lpthread

LIBS = -lm

SDL_PATH = sdl2

SDL2 = SDL2-2.0.9

SDL2_MIXER = SDL2_mixer-2.0.4

SDL2_TTF = SDL2_ttf-2.0.15

EXTRACT = tar -xzf $(SDL_PATH)/$(SDL2).tar.gz -C $(SDL_PATH) && tar -xzf \
            $(SDL_PATH)/$(SDL2_MIXER).tar.gz -C $(SDL_PATH) && tar -xzf \
                $(SDL_PATH)/$(SDL2_TTF).tar.gz -C $(SDL_PATH)

IFLAGS = -I $(INCL) -I $(LIBFT_INCL_PATH)

USER = $(shell whoami)

CC = clang

CFLAGS = -Wall -Werror -Wextra -Ofast #-g -fsanitize=address

RM = rm -rf

ifeq ($(shell uname), Darwin)
	CONFIGURE_SDL2 = cd $(SDL_PATH)/$(SDL2) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2)" && $(MAKE) -j && $(MAKE) install
	CONFIGURE_SDL2_MIXER = cd $(SDL_PATH)/$(SDL2_MIXER) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2)" && $(MAKE) -j && $(MAKE) install
	CONFIGURE_SDL2_TTF = cd $(SDL_PATH)/$(SDL2_TTF) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2)" && $(MAKE) -j && $(MAKE) install
	SDL_LDFLAGS = -L/Users/$(USER)/$(SDL2)/lib -lSDL2 -lSDL2_mixer -lSDL2_ttf
    SDL_CFLAGS = -I/Users/$(USER)/$(SDL2)/include/SDL2 -D_THREAD_SAFE
else
	CONFIGURE_SDL2 = cd $(SDL_PATH)/$(SDL2) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	CONFIGURE_SDL2_MIXER = cd $(SDL_PATH)/$(SDL2_MIXER) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	CONFIGURE_SDL2_TTF = cd $(SDL_PATH)/$(SDL2_TTF) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	SDL_LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib \
	    -Wl,--enable-new-dtags -lSDL2 -lSDL2_mixer -lSDL2_ttf
    SDL_CFLAGS = -I/usr/local/include/SDL2 -D_REENTRANT
endif

all: $(NAME) $(NAME_EDITOR)

$(NAME): $(OBJS)
	@if [ ! -d $(SDL_PATH)/$(SDL2) ] || [ ! -d $(SDL_PATH)/$(SDL2_MIXER) ] \
	    || [ ! -d $(SDL_PATH)/$(SDL2_TTF) ];\
	    then $(EXTRACT); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2)/build ]; then $(CONFIGURE_SDL2); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2_MIXER)/build ]; \
	    then $(CONFIGURE_SDL2_MIXER); fi
	@if [ ! -e $(SDL_PATH)/$(SDL2_TTF)/config.status ]; \
	    then $(CONFIGURE_SDL2_TTF); fi
	@$(MAKE) -j -C libft
	$(CC) $(OBJS) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@

$(NAME_EDITOR): $(OBJS_EDITOR)
	@if [ ! -d $(SDL_PATH)/$(SDL2) ] || [ ! -d $(SDL_PATH)/$(SDL2_MIXER) ] \
	    || [ ! -d $(SDL_PATH)/$(SDL2_TTF) ]; then $(EXTRACT); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2)/build ]; then $(CONFIGURE_SDL2); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2_MIXER)/build ]; \
	    then $(CONFIGURE_SDL2_MIXER); fi
	@if [ ! -e $(SDL_PATH)/$(SDL2_TTF)/config.status ]; \
	    then $(CONFIGURE_SDL2_TTF); fi
	@$(MAKE) -j -C libft
	$(CC) $(OBJS_EDITOR) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCL)
	@if [ ! -d $(SDL_PATH)/$(SDL2) ] || [ ! -d $(SDL_PATH)/$(SDL2_MIXER) ] \
	    || [ ! -d $(SDL_PATH)/$(SDL2_TTF) ]; then $(EXTRACT); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2)/build ]; then $(CONFIGURE_SDL2); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2_MIXER)/build ]; \
	    then $(CONFIGURE_SDL2_MIXER); fi
	@if [ ! -e $(SDL_PATH)/$(SDL2_TTF)/config.status ]; \
	    then $(CONFIGURE_SDL2_TTF); fi
	mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(IFLAGS) $(SDL_CFLAGS) -o $@ -c $<

run: $(NAME)
	./$(NAME) mabite.roflolilolmao

redit: $(NAME_EDITOR)
	./$(NAME_EDITOR) mabite.roflolilolmao

norm:
	norminette $(SRCS) $(INCL)
	$(MAKE) -C libft norm

git: fclean
	git add -A
	git status

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_EDITOR)
	$(RM) mabite.roflolilolmao
	rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_EDITOR)
	$(MAKE) -C libft fclean
	$(RM) $(SDL_PATH)/$(SDL2)
	$(RM) $(SDL_PATH)/$(SDL2_MIXER)
	$(RM) $(SDL_PATH)/$(SDL2_TTF)

re: fclean all
