# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:09:23 by lrandria          #+#    #+#              #
#    Updated: 2022/06/24 04:00:46 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3
OBJS		=	$(SRCS:.c=.o)
HDR			=	./minishell.h
LFT			= 	libft/libft.a
INC			=	-I ./
LIBS		=	-L ./libft -lft -L -lreadline
SRCS		=	1_cmdline_to_lst.c 2_word_to_lst.c 3_syntax_errors.c \
				utils_libft.c utils_nodes.c

all:			$(LFT) $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(LFT):
			make -C ./libft

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

clean:
			rm -rf $(OBJS)
			make -C ./libft clean

fclean:		clean
			rm -rf $(NAME)
			make -C ./libft fclean

re:			fclean all

#verification leaks a supprimer avant correction
leak:
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=ignorereadline ./${NAME}
		
.PHONY:		all bonus clean fclean re
