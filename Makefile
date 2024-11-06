# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 23:48:08 by mtewelde          #+#    #+#              #
#    Updated: 2024/11/06 20:19:03 by mtewelde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g
LIBS      	=	-lXext -lX11 -lm
#libX11.so  || libX11.a && libXext.so || libXext.a || libm.so in usr/lib/x86_64-linux-gnu/ 
RM			=	rm -rf

MLX			=	./minilibx-linux/libmlx.a

SRCS		=	fractol.c\
				src/fract_init.c src/fract_render.c src/events.c src/utils.c src/fractol_utils.c 

OBJ 		= 	$(SRCS:.c=.o)

all: 		$(MLX) $(NAME)
 
$(NAME): 	$(OBJ) $(MLX) $(FTPRINTF)
			@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBS) -o $(NAME)

$(MLX):
			@make -sC ./minilibx-linux

clean:
			@$(RM) $(OBJ)
			@make clean -sC ./minilibx-linux

fclean: 	clean
			@$(RM) $(NAME)
			@$(RM) $(MLX)

re: 		fclean all