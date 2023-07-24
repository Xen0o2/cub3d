# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alecoutr <alecoutr@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/21 13:50:40 by alecoutr          #+#    #+#              #
#    Updated: 2023/07/22 21:41:20 by alecoutr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRCS =	srcs/main.c \
		srcs/init.c \
		srcs/free.c \
		srcs/utils.c \
		srcs/utils2.c \
		srcs/split.c \
		srcs/get_next_line/get_next_line.c
		
OBJS = $(SRCS:.c=.o)

CC = gcc
INC = -I ./includes
FLAGS = -Wall -Wextra -Werror -g -g3

LIBMLX	= libmlx42.a
INCMLX	= -lglfw -L "/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# INCMLX	= -lglfw -L "/Users/$$USER/.brew/opt/glfw/lib/"


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBMLX) $(INC) $(INCMLX)

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o) $(INC)
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all