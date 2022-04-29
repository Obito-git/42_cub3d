NAME		= libvector_2d.a

CC			= gcc

FLAGS		= -Wall -Wextra -Werror

SRCS		= vector_2d.c

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