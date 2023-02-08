NAME = converter

LIBFT_PATH		=	../libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SRC = obj_to_rt.c	\
utils.c 			\

OBJ = $(SRC:.c=.o)

RM = rm -f
ARRC = ar rc

GREEN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

CC = gcc
FLAGS = -Wall -Wextra -Werror -O2 -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIBFT_PATH)
	@echo "$(WHT)Compiling Converter...$(EOC)"
	@$(CC) $(FLAGS) $(LIBFT) $^ -o $@
	@echo "$(GREEN)Converter build completed.$(EOC)"

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	@echo "$(WHT)Removing o-files...$(EOC)"
	$(RM) $(OBJ)
	@ make clean -C ../libft
	@echo "$(GREEN)clean done.$(EOC)"

fclean: clean
	@echo "$(WHT)Removing binary -files...$(EOC)"
	@make fclean -C ../libft
	$(RM) $(NAME)
	@echo "$(GREEN)fclean done.$(EOC)"
