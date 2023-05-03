# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 08:34:51 by yismaail          #+#    #+#              #
#    Updated: 2023/04/07 00:17:49 by yismaail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_isspace.c \
			ft_isempty.c \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstadd_back.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_strcmp.c 

OBJS 	= 	${SRCS:.c=.o}					
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
NAME	=	libft.a

YELLOW		= \e[0;33m
RESET		= \e[0;33m

all		:	${NAME}

$(OBJS) :  $(SRCS)
			@$(CC) $(CFLAGS) -c $(SRCS)

${NAME}	:	${OBJS}
			@printf "$(YELLOW)\rPreparing libft ...\n\n$(RESET)"
			@ar -rc libft.a ${OBJS}

clean	:
			@rm -f $(OBJS) 

fclean	:	clean
			@rm -f ${NAME}

re		:	fclean all