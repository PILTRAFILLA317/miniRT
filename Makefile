NAME = miniRT

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SRC = srcs/main.c	\
srcs/utils.c		\
srcs/al_cam_init.c	\
srcs/light_linked.c	\
srcs/plane_linked.c	\
srcs/sph_linked.c	\
srcs/cyl_linked.c	\

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
FLAGS = -Wall -Wextra -g3 -fsanitize=address -Werror

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	@echo "$(WHT)Compiling MiniRT...$(EOC)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "$(GREEN)miniRT build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@ make clean -C libft
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	@make fclean -C libft
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"


re: fclean all

.PHONY: clean re fclean all bonus m rebonus