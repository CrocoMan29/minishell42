# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 04:04:08 by yismaail          #+#    #+#              #
#    Updated: 2023/03/10 02:14:51 by yismaail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CFLAGS		=	#-Werror -Wextra -Wall 
RM			=	rm -rf
SRCS		=	main.c 
				
OBJS		= ${SRCS:.c=.o}

all			:	$(NAME)

$(NAME)		: $(OBJS)
			make -C libft
			$(CC) $(OBJS) libft/libft.a -o $(NAME)
			
clean		:
			$(RM) $(OBJS)
			make clean -C libft

fclean		: clean
			$(RM) $(NAME)
			make fclean -C libft

re			: fclean all