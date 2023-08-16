# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:50:40 by alecoutr          #+#    #+#              #
#    Updated: 2023/08/16 11:25:54 by alecoutr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS =	srcs/main.c \
		srcs/init_parameters.c \
		srcs/init_values.c \
		srcs/init_map.c \
		srcs/init_map_utils.c \
		srcs/verif.c \
		srcs/draw.c \
		srcs/free.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/utils3.c \
		srcs/utils4.c \
		srcs/split.c \
		srcs/exit.c \
		srcs/hook.c \
		srcs/key_hook.c \
		srcs/resize_hook.c \
		srcs/mouse_hook.c \
		srcs/horizontal_rays.c \
		srcs/vertical_rays.c \
		srcs/texture.c \
		srcs/draw_utils.c \
		srcs/walls.c \
		srcs/minimap.c \
		srcs/player.c \
		srcs/get_next_line/get_next_line.c
		
OBJS = $(SRCS:.c=.o)

CC = gcc
INC = -I ./includes
FLAGS = -Wall -Wextra -Werror -g -g3

#LIBMLX    = libmlx42maison.a
LIBMLX    = libmlx42.a
#INCMLX    = -lglfw -L "/opt/homebrew/Cellar/glfw/3.3.8/lib/"
INCMLX    = -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBMLX) $(INC) $(INCMLX)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o) $(INC)
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:    fclean all
