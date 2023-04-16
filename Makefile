# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 04:04:08 by yismaail          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2023/04/16 02:12:31 by yismaail         ###   ########.fr        #
=======
#    Updated: 2023/04/15 21:30:28 by meharit          ###   ########.fr        #
>>>>>>> e3b1125121ee5ccbee4511bef349884f27def00d
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -fsanitize=address -g
RM			=	rm -rf
SRCS		=	main.c  src/lexer/tokenizer_line.c src/tools/lst_addback_m.c \
				src/tools/lst_env.c src/env/environment.c src/expand/expansion.c \
<<<<<<< HEAD
				src/lexer/checks.c src/parse/parsing.c src/tools/lst_redir.c \
=======
				src/lexer/checks.c \
				src/built-ins/exit.c src/built-ins/env.c \
>>>>>>> e3b1125121ee5ccbee4511bef349884f27def00d
				
OBJS		= ${SRCS:.c=.o}

all			:	$(NAME)

$(NAME)		: $(SRCS)
			make -C libft
			$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME) -lreadline 
			
clean		:
			$(RM) $(OBJS)
			make clean -C libft

fclean		: clean
			$(RM) $(NAME)
			make fclean -C libft

re			: fclean all

.PHONY: all clean fclean re
