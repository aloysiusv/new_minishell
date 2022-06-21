# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:09:23 by lrandria          #+#    #+#              #
#    Updated: 2022/06/21 21:22:36 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
OBJS		=	$(SRCS:.c=.o)
HDR			=	./minishell.h
LIB			=	-lreadline
SRCS		=	1_a_parse_lst_chars.c 1_b_parse_subflags.c \
				
				utils_libft.c utils_nodes.c

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB)

mandatory:		$(NAME)

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) -c -o $@ $< 

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

#verification leaks a supprimer avant correction
leak:
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignorereadline ./${NAME}
		
.PHONY:		all bonus clean fclean re
