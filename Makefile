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
			segment.c \
			player.c \
			serialisation.c \
			walls.c \
			sectors.c \
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

SDL_NAME = SDL2-2.0.9

EXTRACT = tar -xzf $(SDL_NAME).tar.gz

SDL_INCL_PATH = ./$(SDL_NAME)/include

IFLAGS = -I $(INCL) -I $(LIBFT_INCL_PATH) -I $(SDL_INCL_PATH)

USER = $(shell whoami)

CC = clang

CFLAGS = -Wall -Werror -Wextra -Ofast

RM = rm -rf

ifeq ($(shell uname), Darwin)
	CONFIGURE_SDL = cd $(SDL_NAME) && ./configure \
		--prefix="/Users/$(USER)/$(SDL_NAME)" && $(MAKE) -j && $(MAKE) install
	SDL_LDFLAGS = -L/Users/$(USER)/$(SDL_NAME)/lib -lSDL2
	SDL_CFLAGS = -I/Users/$(USER)/$(SDL_NAME)/include/SDL2 -D_THREAD_SAFE
else
	CONFIGURE_SDL = cd $(SDL_NAME) && ./configure \
	    && $(MAKE) -j && sudo $(MAKE) install
	SDL_LDFLAGS = -L/usr/local/lib -Wl,-rpath,/usr/local/lib \
	    -Wl,--enable-new-dtags -lSDL2
	SDL_CFLAGS = -I/usr/local/include/SDL2 -D_REENTRANT
endif

all: $(NAME) $(NAME_EDITOR)

$(NAME): $(OBJS)
	if [ ! -d $(SDL_NAME) ]; then $(EXTRACT); fi
	if [ ! -d $(SDL_NAME)/build ]; then $(CONFIGURE_SDL); fi
	$(MAKE) -j -C libft
	$(CC) $(OBJS) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@

$(NAME_EDITOR): $(OBJS_EDITOR)
	if [ ! -d $(SDL_NAME) ]; then $(EXTRACT); fi
	if [ ! -d $(SDL_NAME)/build ]; then $(CONFIGURE_SDL); fi
	$(MAKE) -j -C libft
	$(CC) $(OBJS_EDITOR) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCL)
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
	$(RM) $(SDL_NAME)

re: fclean all