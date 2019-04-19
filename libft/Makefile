# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfatton <lfatton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/06 18:00:44 by lfatton           #+#    #+#              #
#    Updated: 2018/12/20 22:45:01 by lfatton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, norm, clean, fclean, re

NAME = libft.a

SRC_PATH = srcs

SRC_NAME = ft_putchar.c \
		   ft_putstr.c \
		   ft_putendl.c \
		   ft_putnbr.c \
		   ft_putchar_fd.c \
		   ft_putstr_fd.c \
		   ft_putendl_fd.c \
		   ft_putnbr_fd.c \
		   ft_strlen.c \
		   ft_strcleni.c \
		   ft_nbrlen.c \
		   ft_count_words.c \
		   ft_strrev.c \
		   ft_strcpy.c \
		   ft_strncpy.c \
		   ft_strcmp.c \
		   ft_strncmp.c \
		   ft_strstr.c \
		   ft_strnstr.c \
		   ft_abs.c \
		   ft_dabs.c \
		   ft_sq.c \
		   ft_degtorad.c \
		   ft_radtodeg.c \
		   ft_isspace.c \
		   ft_isblank.c \
		   ft_isalpha.c \
		   ft_isdigit.c \
		   ft_isalnum.c \
		   ft_isascii.c \
		   ft_isprint.c \
		   ft_islower.c \
		   ft_isupper.c \
		   ft_toupper.c \
		   ft_tolower.c \
		   ft_strcat.c \
		   ft_strncat.c \
		   ft_strlcat.c \
		   ft_strchr.c \
		   ft_strrchr.c \
		   ft_memset.c \
		   ft_bzero.c \
		   ft_memcpy.c \
		   ft_memccpy.c \
		   ft_memdup.c \
		   ft_memmove.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_memalloc.c \
		   ft_memdel.c \
		   ft_strnew.c \
		   ft_strdel.c \
		   ft_strclr.c \
		   ft_striter.c \
		   ft_striteri.c \
		   ft_strmap.c \
		   ft_strmapi.c \
		   ft_strequ.c \
		   ft_strnequ.c \
		   ft_strdup.c \
		   ft_strndup.c \
		   ft_strsub.c \
		   ft_strsubfree.c \
		   ft_strtrim.c \
		   ft_strjoin.c \
		   ft_strjoinfree.c \
		   ft_strnjoin.c \
		   ft_strnjoinfree.c \
		   ft_strsplit.c \
		   ft_free_strsplit.c \
		   ft_atoi.c \
		   ft_itoa.c \
		   ft_itoa_base.c \
		   ft_lstnew.c \
		   ft_lstdelone.c \
		   ft_lstdel.c \
		   ft_lstadd.c \
		   ft_lstradd.c \
		   ft_lstiter.c \
		   ft_lstmap.c \
		   get_next_line.c \
		   get_next_line_from_char.c

SRCS = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ_PATH = objs

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJS = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCLS = ./includes/

CC = clang

CFLAGS = -Wall -Werror -Wextra -I $(INCLS) -c -o

LIBS = -lm

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $@ $^
	@ranlib $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $@ $^

norm:
	@norminette $(SRCS) $(INCLS)

git: clean
	@git add -A
	@git status

clean:
	@rm -rf $(OBJS)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	@rm -rf $(NAME)

re: fclean all
