# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aisidore <aisidore@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 17:30:38 by aisidore          #+#    #+#              #
#    Updated: 2025/06/14 19:42:19 by aisidore         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##A refaire pour la partie bonus
C_SRCS = gc/gc_cleanup.c \
		 gc/gc_malloc.c \
		 gc/gc_realloc.c \
		 gc/gc_remove.c \
		 parsing/get_next_line.c \
		 parsing/get_next_line_utils.c \
		 parsing/utils.c \
		 parsing/parsing.c \
		 parsing/parsing_get_texture.c \
		 parsing/parsing_check_texture.c \
		 parsing/parsing_check_color.c \
		 parsing/parsing_extention.c \
		 parsing/parsing_get_map.c \
		 parsing/parsing_flood_fill.c \
		 src/init.c \
		 src/exit.c \
		 src/hook_utils.c \
		 src/hook.c \
		 src/display.c \
		 src/texture_utils.c \
		 src/texture.c \
		 src/map.c

SRCS =  src/main.c $(C_SRCS)

BONUS_SRCS = src/main_bonus.c $(C_SRCS)

C_OBJS = objets/gc_cleanup.o \
		 objets/gc_malloc.o \
		 objets/gc_realloc.o \
		 objets/gc_remove.o \
		 objets/get_next_line.o \
		 objets/get_next_line_utils.o \
		 objets/utils.o \
		 objets/parsing.o \
		 objets/parsing_get_texture.o \
		 objets/parsing_check_texture.o \
		 objets/parsing_check_color.o \
		 objets/parsing_extention.o \
		 objets/parsing_get_map.o \
		 objets/parsing_flood_fill.o \
		 objets/init.o \
		 objets/stop.o \
	   	 objets/hook_utils.o \
	   	 objets/hook.o \
	   	 objets/display.o \
	   	 objets/texture_utils.o \
	   	 objets/texture.o \
	   	 objets/map.o

OBJS = objets/main.o

BONUS_OBJS = objets/main_bonus.o

PTH = /home/aisidore/Downloads/minilibx-linux/

NAME = cub3D
BONUS_NAME = cub3D_bonus

FLAGS = -Wall -Wextra -Werror -I.
MFLAGS = -lm -lmlx -lX11 -lXext -O3

all: $(NAME)
$(NAME): $(C_OBJS) $(OBJS)
	cc $(FLAGS) $(C_OBJS) $(OBJS) -L$(PTH) $(MFLAGS) -o $(NAME)

objets/%.o: src/%.c
	mkdir -p objets
	cc $(FLAGS) -c $< -o $@
objets/%.o: parsing/%.c
	@mkdir -p objets
	cc $(FLAGS) -c $< -o $@
objets/%.o: gc/%.c
	@mkdir -p objets
	cc $(FLAGS) -c $< -o $@

bonus : $(BONUS_NAME)
$(BONUS_NAME): $(C_OBJS) $(BONUS_OBJS)
	cc $(FLAGS) $(C_OBJS) $(BONUS_OBJS) -L$(PTH) $(MFLAGS) -o $(BONUS_NAME)

clean:
	rm -f objets/*.o

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all
rebonus: fclean bonus
	
.PHONY: all bonus clean fclean re rebonus