# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 23:48:08 by mtewelde          #+#    #+#              #
#    Updated: 2024/10/29 20:48:59 by mtewelde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
LIBS      	=	-lXext -lX11 -lm
RM			=	rm -rf

MLX			=	./minilibx-linux/libmlx.a

SRCS		=	fractol.c fract_init.c fract_render.c key_events.c utils.c 

OBJ 		= 	$(SRCS:.c=.o)

all: 		$(MLX) $(NAME)

$(NAME): 	$(OBJ) $(MLX)
			@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBS) -o $(NAME)

$(MLX):
			@make -C ./minilibx-linux

clean:
			@$(RM) $(OBJ)
			@make clean -C ./minilibx-linux

fclean: 	clean
			@$(RM) $(NAME)
			@$(RM) $(MLX)

re: 		fclean all