NAME = miniRT

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SRC = main.c

OBJ = $(SRC:.c=.o)

RM = rm -f
ARRC = ar rc

GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

HEADERS = minirt.h
CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=address

all: $(NAME)

m: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	@echo "$(WHT)Compiling Philosophers...$(EOC)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(GREEN)miniRT build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"


re: fclean all

.PHONY: clean re fclean all bonus m rebonus