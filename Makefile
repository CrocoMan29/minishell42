# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 04:04:08 by yismaail          #+#    #+#              #
#    Updated: 2023/05/01 16:48:08 by meharit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -fsanitize=address -g
RM			=	rm -rf
SRCS		=	main.c check_tokens.c  src/lexer/tokenizer_line.c src/tools/lst_addback_m.c \
				src/tools/lst_env.c src/env/environment.c src/expand/expansion.c \
				src/lexer/checks.c src/parse/parsing.c src/tools/lst_redir.c \
				src/tools/lst_cmd.c \
				src/built-ins/pwd.c src/built-ins/exit.c src/built-ins/env.c src/built-ins/unset.c \
				src/exec/execution.c  src/built-ins/cd.c src/built-ins/echo.c  \
				src/built-ins/export.c src/built-ins/exp_uti.c \

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
