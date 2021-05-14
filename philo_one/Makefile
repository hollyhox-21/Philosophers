# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjoella <rjoella@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 15:23:08 by rjoella           #+#    #+#              #
#    Updated: 2021/05/14 15:33:46 by rjoella          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
FILE_CUB = main \
			actions \
			enter_point \
			ft_atoi \
			ft_bzero \
			ft_itoa \
			ft_strjoin \
			ft_strlen \
			init_struct \
			utils

OBJ_CUB = $(patsubst %,%.o,$(FILE_CUB))

CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all:
# компиляция в 4 потока (скорость)
	$(MAKE) $(NAME) -j 4
$(NAME): $(OBJ_CUB) ./include/philo_one.h
	gcc $(CFLAGS) $(OBJ_CUB) -o $(NAME)

$(OBJ_CUB): %.o:./src/%.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	@rm -f ./*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

norm:
	@norminette ./src ./include