NAME = miniRT

LIBFT_PATH		=	./libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MLX_PATH		=	./mlx
MLX				=	$(MLX_PATH)/libmlx.a

SRC = srcs/main.c	\
srcs/elem_init.c	\
srcs/iw_sph_iter.c	\
srcs/iw_cyl_iter.c	\
srcs/iw_plane_iter.c\
srcs/utils.c		\
srcs/al_cam_init.c	\
srcs/light_linked.c	\
srcs/plane_linked.c	\
srcs/sph_linked.c	\
srcs/cyl_linked.c	\
srcs/ray_caster.c	\
srcs/vec_utils.c	\
srcs/color_utils.c	\
srcs/cyl_inter.c	\
srcs/sph_inter.c	\
srcs/pl_inter.c		\
srcs/light_comb.c	\
srcs/inter_with.c	\
srcs/tri_linked.c	\
srcs/tri_inter.c	\
srcs/mirrors.c		\
srcs/color_fun.c	\
srcs/utils2.c		\
srcs/first_inter.c	\

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
FLAGS = -Wall -Wextra -Werror -O2 -pthread -g3 -Ofast #-fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	make -C mlx
	@echo "$(WHT)Compiling MiniRT...$(EOC)"
	@$(CC) $(FLAGS) -lmlx -Lmlx -framework OpenGL -framework AppKit $(LIBFT) $(MLX) $^ -o $@
	@echo "$(GREEN)miniRT build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@ make clean -C libft
	@ make clean -C mlx
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	@make fclean -C libft
	@make clean -C mlx
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"


re: fclean all

.PHONY: clean re fclean all bonus m rebonus
