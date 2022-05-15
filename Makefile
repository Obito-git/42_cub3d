# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/02 14:32:03 by lnelson           #+#    #+#              #
#    Updated: 2022/02/10 19:42:40 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

SRCS_DIR	= srcs/

OBJS_DIR	= objs/

INCLS_DIR	= includes/

LIBS_DIR	= libs/

CFLAGS		=  -g3 -Wall -Wextra -Werror -I ${INCLS_DIR} 

MLX_FLAGS	= -L${LIBS_DIR}minilibx-linux -lmlx -lX11 -lm -lXext -lbsd

FLAGS		= -L${LIBS_DIR}libft -lft -L${LIBS_DIR}2d_ftmath -l2d_ftmath

CC			= gcc

SRCS		=	main.c\
				exits.c\
				main_utils.c\
				key_hooks.c\
				render/render.c\
				render/calculations.c\
				render/minimap.c\
				parsing/parsing.c\
				parsing/add_textures.c\
				parsing/add_minimap_textures.c\
				parsing/map_processing.c\
				parsing/parsing_utils.c\

OBJS		= ${SRCS:.c=.o}

OBJS		:= ${addprefix ${OBJS_DIR}, ${OBJS}}

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
			${CC} ${CFLAGS} -c $< -o $@

all:		${NAME}


${NAME}:	${OBJS}
			make -C ${LIBS_DIR}libft
			make -C ${LIBS_DIR}minilibx-linux
			make -C ${LIBS_DIR}2d_ftmath
			${CC} -o $@ ${OBJS} ${FLAGS} ${MLX_FLAGS}


sanitize:	${OBJS}
			make -C ${LIBS_DIR}libft
			make -C ${LIBS_DIR}minilibx-linux
			make -C ${LIBS_DIR}2d_ftmath
			${CC} -o $@ ${OBJS} ${FLAGS} ${MLX_FLAGS} -g3 -fsanitize=address	

clean:
			make clean -C ${LIBS_DIR}libft
			make clean -C ${LIBS_DIR}minilibx-linux
			make clean -C ${LIBS_DIR}2d_ftmath
			${RM} ${OBJS}
			
fclean:		clean
			make fclean -C ${LIBS_DIR}libft
			make fclean -C ${LIBS_DIR}2d_ftmath
			make clean -C ${LIBS_DIR}minilibx-linux
			${RM} ${NAME} sanitize

re:			fclean all

RM			= rm -f
