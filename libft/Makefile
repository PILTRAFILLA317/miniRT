# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: becastro <becastro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 12:04:06 by umartin-          #+#    #+#              #
#    Updated: 2023/03/23 15:50:06 by becastro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_bzero.c \
ft_memcpy.c \
ft_memmove.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_memchr.c \
ft_memcmp.c\
ft_strnstr.c\
ft_atoi.c \
ft_calloc.c \
ft_strdup.c \
ft_substr.c \
ft_strtrim.c \
ft_strjoin.c \
ft_split.c \
ft_itoa.c \
ft_strmapi.c \
ft_striteri.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
get_next_line.c \
get_next_line_utils.c \
ft_printf.c \
ft_put.c \
ft_puthexa.c \
ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_doubleprint.c \
ft_doublestrlen.c \
ft_doublefree.c \
ft_filelen.c	\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra

HEADERS = libft.h
CC = gcc
RM = rm -f
ARRC = ar rc

all: $(NAME)

$(NAME): $(OBJ)
	$(ARRC) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean re fclean all bonus
