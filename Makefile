# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:30:38 by aisidore          #+#    #+#              #
#    Updated: 2025/06/14 12:41:20 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##A refaire pour la partie bonus
C_SRCS = src/init.c \
		 src/exit.c \
		 src/hook_utils.c \
		 src/hook.c \
		 src/display.c \
		 src/texture_utils.c \
		 src/texture.c \
		 src/map.c

SRCS =  src/main.c $(C_SRCS)

BONUS_SRCS = src/zmain_bonus.c $(C_SRCS)

OBJS = objets/main.o \
	   objets/init.o \
	   objets/exit.o \
	   objets/hook_utils.o \
	   objets/hook.o \
	   objets/display.o \
	   objets/texture_utils.o \
	   objets/texture.o \
	   objets/map.o
BONUS_OBJS = objets/zmain_bonus.o \
			 objets/init.o \
			 objets/exit.o \
			 objets/hook_utils.o \
			 objets/hook.o \
			 objets/zhook_bonus.o \
			 objets/display.o \
			 objets/zdisplay_bonus.o \
			 objets/texture_utils.o \
			 objets/texture.o \
			 objets/map.o
PTH = /home/aisidore/Downloads/minilibx-linux/

NAME = cub3d
BONUS_NAME = cub3d_bonus

FLAGS = -Wall -Wextra -Werror -I.
MFLAGS = -lm -lmlx -lX11 -lXext -O3

all: $(NAME)
$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -L$(PTH) $(MFLAGS) -o $(NAME)
objets/%.o: src/%.c
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