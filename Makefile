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

.PHONY: all, extract, run, debug, editor, norm, git, clean, fclean, re

NAME = doom-nukem
EDITOR_NAME = editor

SRC_PATH = srcs

SRC_NAME =	main.c \
			vector.c \
			segment.c \
			player.c \
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
			time.c \
			weapons.c \
			weapon_draw.c \
			utils.c

SRC_EDITOR_NAME = editor.c

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
SRCS_EDITOR = $(addprefix $(SRC_PATH)/,$(SRC_EDITOR_NAME))

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)
EDITOR_NAME_OBJ = $(SRC_EDITOR_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
EDITOR_OBJS = $(addprefix $(OBJ_PATH)/,$(EDITOR_NAME_OBJ))

INCL_PATH = includes

INCL_NAME = doom.h

INCL = $(addprefix $(INCL_PATH)/,$(INCL_NAME))

LIBFT_INCL_PATH = ./libft/includes

LDLIBFT = -L ./libft -lft

LIBS = -lm

SDL_NAME = SDL2-2.0.9

EXTRACT = tar -xzf $(SDL_NAME).tar.gz

SDL_INCL_PATH = ./$(SDL_NAME)/include

IFLAGS = -I $(INCL_PATH) -I $(LIBFT_INCL_PATH) -I $(SDL_INCL_PATH)

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

all: $(NAME)

$(NAME): $(OBJS) $(EDITOR_OBJS)
	if [ ! -d $(SDL_NAME) ]; then $(EXTRACT); fi
	if [ ! -d $(SDL_NAME)/build ]; then $(CONFIGURE_SDL); fi
	$(MAKE) -j -C libft
	$(CC) $(OBJS) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $@
	$(CC) $(EDITOR_OBJS) $(LDLIBFT) $(LIBS) $(SDL_LDFLAGS) -o $(EDITOR_NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INCL)
	mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(IFLAGS) $(SDL_CFLAGS) -o $@ -c $<

run: all
	./$(NAME)

editor: all
	./$(EDITOR_NAME)

debug: all
	./$(NAME) debug

norm:
	norminette $(SRCS) $(INCL)
	$(MAKE) -C libft norm

git: fclean
	git add -A
	git status

clean:
	$(RM) $(OBJS)
	$(RM) $(EDITOR_OBJS)
	rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	$(RM) $(NAME)
	$(RM) $(EDITOR_NAME)
	$(MAKE) -C libft fclean
	$(RM) $(SDL_NAME)

re: fclean all
