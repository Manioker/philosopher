# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anvacca <anvacca@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/18 14:33:54 by anvacca           #+#    #+#              #
#    Updated: 2024/09/26 15:17:51 by anvacca          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Executable
EXE			=	philo

# Files
SRC			=	./src/main.c \
				./src/parsing.c \
				./src/routine.c \

SRC_UTILS	=	./src/utils/ft_atoui.c \
				./src/utils/ft_get_time.c \
				./src/utils/ft_wait.c \


SOURCES		=	${SRC} ${SRC_UTILS}
OBJECTS		=	${SOURCES:%.c=obj/%.o}

# Variables
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -g
RM			=	rm -rf

# Makefile
all:		${EXE}

${EXE}:		${OBJECTS}
			@${CC} ${CFLAGS} ${OBJECTS} -o ${EXE}

obj/%.o:	%.c
			@mkdir -p obj/$(dir $<)
			@${CC} ${CFLAGS} -c $< -o $@

clean:
			@${RM} obj

fclean:		clean
			@${RM} ${EXE}

re:			fclean all

.PHONY:		all clean fclean re
