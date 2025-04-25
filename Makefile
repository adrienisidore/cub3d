# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:30:38 by aisidore          #+#    #+#              #
#    Updated: 2025/04/23 14:19:01 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_SRCS = main.c
		
SRCS =  $(C_SRCS)

BONUS_SRCS = $(C_SRCS)
			
OBJS = objets/main.o
BONUS_OBJS = objets/main.o
PTH = /home/aisidore/Documents/minilibx-linux/

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