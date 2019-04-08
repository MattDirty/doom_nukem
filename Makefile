# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/07 17:35:48 by lfatton           #+#    #+#              #
#    Updated: 2019/03/08 15:34:39 by lfatton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, extract, run, redit, debug, editor, norm, git, clean, fclean, re

NAME = doom-nukem

NAME_EDITOR = editor

SRC_PATH = srcs

SRCS_NAMES = vector.c \
			collision.c \
			segment.c \
			player.c \
			serialisation.c \
			walls.c \
			sectors.c \
			map.c \
			environment.c \
			loop.c \
			engine.c \
			motion.c \
			render_utils.c \
			render.c \
			debug_init.c \
			debug_draw_tools.c \
			draw_tools.c \
			ui_draw.c \
			timer_handler.c \
			time.c \
			weapons.c \
			weapon_draw.c \
			utils.c \
			animation.c \
			melee.c \
			skybox.c \
			config.c \
			textures.c

SRC_NAME =	main.c \
			$(SRCS_NAMES)

SRC_EDITOR_NAME = editor.c \
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

LDLIBFT = -L ./libft -lft

LIBS = -lm

SDL_PATH = sdl2

SDL2 = SDL2-2.0.9

SDL2_MIXER = SDL2_mixer-2.0.4

SDL2_TTF = SDL2_ttf-2.0.15

EXTRACT = tar -xzf $(SDL_PATH)/$(SDL2).tar.gz -C $(SDL_PATH) && tar -xzf \
            $(SDL_PATH)/$(SDL2_MIXER).tar.gz -C $(SDL_PATH) && tar -xzf \
                $(SDL_PATH)/$(SDL2_TTF).tar.gz -C $(SDL_PATH)

SDL2_INCL_PATH = ./$(SDL_PATH)/$(SDL2)/include

SDL2_MIXER_INCL_PATH = ./$(SDL_PATH)/$(SDL2_MIXER)

SDL2_TTF_INCL_PATH = ./$(SDL_PATH)/$(SDL2_TTF)

IFLAGS = -I $(INCL) -I $(LIBFT_INCL_PATH) -I $(SDL2_INCL_PATH) \
            -I $(SDL2_MIXER_INCL_PATH) -I $(SDL2_TTF_INCL_PATH)

USER = $(shell whoami)

CC = clang

CFLAGS = -Wall -Werror -Wextra -Ofast

RM = rm -rf

ifeq ($(shell uname), Darwin)
	CONFIGURE_SDL2 = cd $(SDL_PATH)/$(SDL2) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2)" && $(MAKE) -j && $(MAKE) install
	CONFIGURE_SDL2_MIXER = cd $(SDL_PATH)/$(SDL2_MIXER) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2_MIXER)" && $(MAKE) -j && $(MAKE) install
	CONFIGURE_SDL2_TTF = cd $(SDL_PATH)/$(SDL2_MIXER) && ./configure \
		--prefix="/Users/$(USER)/$(SDL2_TTF)" && $(MAKE) -j && $(MAKE) install
	SDL_LDFLAGS = $(shell sdl-config --libs) -lSDL2 -lSDL2_mixer -lSDL2_ttf
	SDL_CFLAGS = $(shell sdl-config --cflags)
else
	CONFIGURE_SDL2 = cd $(SDL_PATH)/$(SDL2) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	CONFIGURE_SDL2_MIXER = cd $(SDL_PATH)/$(SDL2_MIXER) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	CONFIGURE_SDL2_TTF = cd $(SDL_PATH)/$(SDL2_TTF) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	SDL_LDFLAGS = $(shell sdl-config --libs) -lSDL2 -lSDL2_mixer -lSDL2_ttf
	SDL_CFLAGS = $(shell sdl-config --cflags)
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
		|| [ ! -d $(SDL_PATH)/$(SDL2_TTF) ];\
		then $(EXTRACT); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2)/build ]; then $(CONFIGURE_SDL2); fi
	@if [ ! -d $(SDL_PATH)/$(SDL2_MIXER)/build ]; \
		then $(CONFIGURE_SDL2_MIXER); fi
	@if [ ! -e $(SDL_PATH)/$(SDL2_TTF)/config.status ]; \
		then $(CONFIGURE_SDL2_TTF); fi
	mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(IFLAGS) $(SDL_CFLAGS) -o $@ -c $<

run: $(NAME)
	./$(NAME)

redit: $(NAME_EDITOR)
	./$(NAME_EDITOR)

debug: $(NAME)
	./$(NAME) debug

norm:
	norminette $(SRCS) $(INCL)
	$(MAKE) -C libft norm

git: fclean
	git add -A
	git status

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_EDITOR)
	rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_EDITOR)
	$(MAKE) -C libft fclean
	$(RM) $(SDL_PATH)/$(SDL2)
	$(RM) $(SDL_PATH)/$(SDL2_MIXER)
	$(RM) $(SDL_PATH)/$(SDL2_TTF)

re: fclean all
