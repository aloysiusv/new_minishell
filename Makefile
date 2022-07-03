# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 19:09:23 by lrandria          #+#    #+#              #
#    Updated: 2022/07/03 18:04:21 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -fsanitize=address
OBJS		=	$(SRCS:.c=.o)
HDR			=	./inc/minishell.h
LFT			= 	libft/libft.a
INC			=	-I ./inc
LIBS		=	-L ./libft -lft -lreadline
SRCS		=	0_main.c \
				parser/1_get_lst_chars.c \
				parser/1_set_chars_subflags.c \
				parser/1_set_expansion_flags.c \
				parser/2_get_lst_tokens.c \
				parser/3_get_expansions.c \
				parser/3_get_lst_expanded.c \
				parser/4_syntax_errors.c \
				parser/5_get_tab_cmds.c \
				parser/5_set_tab_flags.c \
				env/create_lst_env.c \
				env/get_envp.c \
				exec/exec_builtin.c \
				builtins/ft_echo.c \
				signals.c \
				heredoc.c heredoc_expand1.c heredoc_expand2.c heredoc_expand3.c \
				utils.c \
				utils_tab_cmds.c \
				utils_lst_delete.c utils_lst_nodes.c utils_lst_env.c \
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
leak:		$(LFT) $(NAME)
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=doc/ignorereadline ./${NAME}
		
.PHONY:		all clean fclean re leak
