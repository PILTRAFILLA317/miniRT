NAME = ../miniRT_bonus

LIBFT_PATH		=	../libft
LIBFT			=	$(LIBFT_PATH)/libft.a

MLX_PATH		=	../mlx
MLX				=	$(MLX_PATH)/libmlx.a

SRC = srcs/main_bonus.c		\
srcs/main_init_bonus.c		\
srcs/thread_manager_bonus.c	\
srcs/id_getter_bonus.c		\
srcs/elem_getter_bonus.c		\
srcs/elem_getter_uts_bonus.c	\
srcs/elem_init_bonus.c		\
srcs/mirror_utils_bonus.c		\
srcs/light_comb_inits_bonus.c	\
srcs/vec_math_bonus.c			\
srcs/vec_mult_math_bonus.c	\
srcs/vec_unit_cross_bonus.c	\
srcs/iw_sph_iter_bonus.c		\
srcs/iw_cyl_iter_bonus.c		\
srcs/iw_plane_iter_bonus.c	\
srcs/iw_disc_iter_bonus.c		\
srcs/iw_tri_iter_bonus.c		\
srcs/utils_bonus.c			\
srcs/al_cam_init_bonus.c		\
srcs/light_linked_bonus.c		\
srcs/plane_linked_bonus.c		\
srcs/sph_linked_bonus.c		\
srcs/cyl_linked_bonus.c		\
srcs/ray_caster_bonus.c		\
srcs/vec_utils_bonus.c		\
srcs/color_utils_bonus.c		\
srcs/cyl_inter_bonus.c		\
srcs/sph_inter_bonus.c		\
srcs/pl_inter_bonus.c			\
srcs/light_comb_bonus.c		\
srcs/inter_with_bonus.c		\
srcs/tri_linked_bonus.c		\
srcs/tri_inter_bonus.c		\
srcs/mirrors_bonus.c			\
srcs/color_fun_bonus.c		\
srcs/utils2_bonus.c			\
srcs/first_inter_bonus.c		\

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
	make -C ../libft
	make -C ../mlx
	@echo "$(WHT)Compiling MiniRT...$(EOC)"
	@$(CC) $(FLAGS) -lmlx -L../mlx -framework OpenGL -framework AppKit $(LIBFT) $(MLX) $^ -o $@
	@echo "$(GREEN)miniRT bonus build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -Imlx -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@ make clean -C ../libft
	@ make clean -C ../mlx
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	@make fclean -C ../libft
	@make clean -C ../mlx
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"


re: fclean all

.PHONY: clean re fclean all bonus m rebonus
