# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:30:38 by aisidore          #+#    #+#              #
#    Updated: 2025/04/28 16:46:11 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_SRCS = main.c map.c

SRCS =  $(C_SRCS)

BONUS_SRCS = $(C_SRCS)

OBJS = objets/main.o objets/map.o
BONUS_OBJS = objets/main.o objets/map.o
PTH = /home/aisidore/Downloads/minilibx-linux/

NAME = cub3d
BONUS_NAME = cub3d_bonus

FLAGS = -Wall -Wextra -Werror
MFLAGS = -lm -lmlx -lX11 -lXext -O3

all: $(NAME)
$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -L$(PTH) $(MFLAGS) -o $(NAME)
objets/%.o: %.c
	mkdir -p objets
	cc $(FLAGS) -c $< -o $@
bonus : $(BONUS_NAME)
$(BONUS_NAME): $(BONUS_OBJS)
	cc $(FLAGS) $(BONUS_OBJS) -L$(PTH) $(MFLAGS) -o $(BONUS_NAME)

clean:
	rm -f objets/*.o

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
rebonus: fclean bonus
	
.PHONY: all bonus clean fclean re rebonus