# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 04:04:08 by yismaail          #+#    #+#              #
#    Updated: 2023/06/17 08:54:26 by yismaail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc

CFLAGS		=	 -Werror -Wextra -Wall -lreadline -fsanitize=address -g3#-L/goinfre/meharit/homebrew/opt/readline/lib 
RM			=	rm -rf
SRCS		=	minishell_mess.c my_libft.c my_libft2.c main.c signals.c src/lexer/tokenizer_line.c src/tools/lst_addback_m.c \
				src/tools/lst_env.c src/envir/environment.c src/expand/expansion.c \
				src/expand/expansion2.c src/expand/expansion3.c  \
				src/lexer/checks.c src/parse/parsing.c src/parse/parsing2.c src/tools/lst_redir.c \
				src/tools/lst_cmd.c \
				src/built-ins/pwd.c src/built-ins/exit.c src/built-ins/env.c src/built-ins/unset.c \
				src/built-ins/cd.c src/built-ins/cd_uti.c src/built-ins/echo.c src/built-ins/export.c  src/built-ins/exp_uti.c  \
				src/exec/pipes.c src/exec/pipes_uti.c src/exec/exec_single.c src/exec/cmd_exist.c src/exec/child_proc.c src/exec/execution.c src/exec/exec_built.c \
				src/exec/file_management.c src/exec/herdoc.c src/exec/herdoc_uti.c  check_tokens.c\

RED			= \e[0;31m				
YELLOW		= \e[0;33m
GREEN		= \e[0;92m
RESET    	= \033[0m

OBJS		= ${SRCS:.c=.o}

all			:	$(NAME)

$(NAME)		: $(SRCS)
			@printf "$(YELLOW)\rMinishell loading ...⏳\n$(RESET)"
			@make -C libft
			@$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME) -lreadline 
			@printf "$(GREEN)\rMinishell Ready \n$(RESET)"    #### why /r ??
			
clean		:
			@printf "$(RED)\rCleaning ... 🗑️\n"
			@$(RM) $(OBJS)
			@make clean -C libft

fclean		: clean
			@$(RM) $(NAME)
			@make fclean -C libft

re			: fclean all

.PHONY: all clean fclean re