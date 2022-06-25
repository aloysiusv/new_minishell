# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:09:23 by lrandria          #+#    #+#              #
#    Updated: 2022/06/25 12:18:49 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3
OBJS		=	$(SRCS:.c=.o)
HDR			=	./inc/minishell.h
LFT			= 	libft/libft.a
INC			=	-I ./inc
LIBS		=	-L ./libft -lft -L -lreadline
SRCS		=	parser/1_get_lst_chars.c parser/1_get_lst_chars2.c \
				parser/2_get_lst_tokens.c \
				parser/3_syntax_errors.c \
				parser/4_expansions.c \
				env/create_env.c \
				signals.c \
				utils_nodes_tokens.c utils_nodes_var.c \
				utils_errors.c utils_free.c \

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
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=doc/ignorereadline ./${NAME}
		
.PHONY:		all bonus clean fclean re
