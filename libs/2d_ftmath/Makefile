# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnelson <lnelson@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/08 16:39:09 by lnelson           #+#    #+#              #
#    Updated: 2022/05/08 16:54:10 by lnelson          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lib2d_ftmath.a

CC			= gcc

FLAGS		= -Wall -Wextra -Werror

SRCS		= line.c point.c segment.c vector.c

OBJS		= ${SRCS:.c=.o}

.c.o:
			${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

clean:		
			${RM} ${OBJS}
				
fclean:		clean
			${RM} ${NAME}
				
re:			fclean all

RM			= rm -fr