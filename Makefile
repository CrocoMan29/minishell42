# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 04:04:08 by yismaail          #+#    #+#              #
#    Updated: 2023/03/17 05:27:13 by yismaail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	-Werror -Wextra -Wall -lreadline
RM			=	rm -rf
SRCS		=	main.c  src/lexer/tokenizer_line.c src/lst_func/lst_addback_m.c
				
OBJS		= ${SRCS:.c=.o}

all			:	$(NAME)

$(NAME)		: $(SRCS)
			make -C libft
			$(CC) $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME)
			
clean		:
			$(RM) $(OBJS)
			make clean -C libft

fclean		: clean
			$(RM) $(NAME)
			make fclean -C libft

re			: fclean all

.PHONY: all clean fclean re