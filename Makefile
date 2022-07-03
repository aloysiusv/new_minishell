# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lrandria <lrandria@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/03 20:18:49 by lrandria          #+#    #+#              #
#    Updated: 2022/07/03 20:31:50 by lrandria         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g3
OBJS		=	$(SRCS:.c=.o)
HDR			=	./incs/minishell.h
LFT			= 	libft/libft.a
INC			=	-I ./incs
LIBS		=	-L ./libft -lft -lreadline
SRCS		=	srcs/main.c \
				srcs/parser/1_get_lst_chars.c srcs/parser/1_set_chars_subflags.c srcs/parser/1_set_expansion_flags.c \
				srcs/parser/2_get_lst_tokens.c \
				srcs/parser/3_get_lst_expanded.c srcs/parser/3_get_expansions.c \
				srcs/parser/4_syntax_errors.c \
				srcs/parser/5_get_tab_cmds.c \
				srcs/parser/5_set_tab_flags.c \
				srcs/builtin/test.c \
				srcs/builtin/echo.c \
				srcs/builtin/pwd.c srcs/builtin/cd.c \
				srcs/builtin/env.c srcs/builtin/export.c srcs/builtin/unset.c \
				srcs/builtin/exit.c \
				srcs/env/parse.c \
				srcs/env/find.c srcs/env/convert.c \
				srcs/env/free.c srcs/env/utils.c \
				srcs/exec/execute.c \
				srcs/exec/builtin.c srcs/exec/command.c \
				srcs/exec/redirect.c srcs/exec/files.c srcs/exec/path.c \
				srcs/heredoc/heredoc.c \
				srcs/heredoc/heredoc_expand1.c srcs/heredoc/heredoc_expand2.c srcs/heredoc/heredoc_expand3.c \
				srcs/signal/signal.c \
				srcs/utils/utils.c \
				srcs/utils/utils_errors.c \
				srcs/utils/utils_tab_cmds.c srcs/utils/utils_lst_nodes.c \
				srcs/utils/utils_lst_delete.c srcs/utils/utils_free.c \

all:			$(LFT) $(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

$(LFT):
			make -C ./libft

%.o:		%.c $(HDR)
			$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

# valgrind:		all
# 				/bin/valgrind \
# 		--leak-check=full \
# 		--show-leak-kinds=all \
# 		--trace-children=yes \
# 		--track-origins=yes \
# 		--track-fds=yes \
# 		--error-limit=no \
# 		--gen-suppressions=all \
# 		--suppressions=bin.supp \
# 		--suppressions=readline.supp \
# 		--log-file=valgrind.log \
# 		./$(NAME)

clean:
			rm -rf $(OBJS)
			make -C ./libft clean

fclean:		clean
			rm -rf $(NAME)
			make -C ./libft fclean

re:			fclean all

.PHONY:		all clean fclean re
