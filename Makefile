# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtewelde <mtewelde@student.42lehavre.fr    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/14 23:48:08 by mtewelde          #+#    #+#              #
#    Updated: 2024/10/28 19:30:47 by mtewelde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	fractol

CC		=	cc
CFLAGS		=	-Wall -Werror -Wextra
LIBS      	=	-lXext -lX11 -lm
RM		=	rm -rf

MLX		=	./minilibx-linux/libmlx.a
INC		=	minilibx-linux/

SRCS		=	fractol.c fract_init.c fract_render.c fract_util.c key_events.c utils.c 

OBJ 		= 	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

all: 		$(MLX) $(NAME)

$(NAME): 	$(OBJ) $(MLX)
			@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBS) -o $(NAME)

$(MLX):
			@make -sC ./minilibx-linux

clean:
			@$(RM) $(OBJ)
			@make clean -C ./minilibx-linux

fclean: 	clean
			@$(RM) $(NAME)
			@$(RM) $(MLX)

re: 		fclean all
