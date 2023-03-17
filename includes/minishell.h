/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/17 05:36:34 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

int	g_exit_status;

typedef struct s_lexer
{
	
}		t_lexer;

typedef struct s_token
{
	int		type;
	char	*content;
	struct s_token *next;
}		t_token;

enum {
	WORD,
	PIPE,
	FILEIN,
	FILEOUT,
	OPERATOR,
};

/*

typedef struct lexer
{
	char	c;
	int		i;
	char	*value;
}			lexer;

typedef struct tokens
{
	enam{
		
	}l;
	char *p;
}		tokens;

typedef struct parser
{
	int		type;
	char	*value;
	struct t_token *next;
}		parser;

typedef struct t_redi
{
	enam{
		1,in
		2,out
		3,append
		4,herdoc
	}l;
	char *filename;
	int fd;
	struct t_redi *next;
}		t_redi;

typedef struct data
{
	char	**value;
	t_redi	*redi;
	struct t_token *next;
	int	in_out[2];
}		data;

*/

//*----------LEXER----------*//
int	token_line(char *line, t_token **token);
int	take_separator(char *line, t_token **token);
int	whish_separator(char *line);
void	check_args(int ac, char **av);


//*---------lst_func--------*//
t_token  *ft_lstnew_m(char *content);
t_token  *ft_lstlast_m(t_token *lst);
void    ft_lstadd_back_m(t_token **lst, t_token *new);

#endif