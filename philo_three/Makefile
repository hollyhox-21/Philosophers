NAME = philo_three
FILE_CUB = main \
			actions \
			entry_point \
			ft_atoi \
			ft_bzero \
			ft_itoa \
			ft_strjoin \
			ft_strlen \
			init_struct \
			ft_isdigit \
			validation \
			utils

OBJ_CUB = $(patsubst %,%.o,$(FILE_CUB))

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all:
	@$(MAKE) $(NAME) -j 4
$(NAME): $(OBJ_CUB) ./include/philo_three.h
	@echo "\x1B[33mProgramm is building ...\033[0m"
	@gcc $(CFLAGS) $(OBJ_CUB) -o $(NAME)
	@echo "\x1B[32m===> Programm is ready <===\033[0m"

$(OBJ_CUB): %.o:./src/%.c
	@gcc -c $(CFLAGS) $< -o $@

clean:
	@rm -f ./*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette ./src ./include