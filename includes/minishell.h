/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/03 05:29:50 by yismaail         ###   ########.fr       */
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

//int	g_exit_status;
char	**g_env;

typedef struct s_lexer
{
	
}		t_lexer;

typedef struct s_redi
{
	enum {
		in,
		out,
		append,
		herdoc,
	}redir;
	char			*file;
	struct s_redi	*next;
}					t_redi;

typedef struct s_token
{
	int		type;
	char	*content;
	int		expand;
	struct s_token *next;
}		t_token;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env	*next;
}					t_env;

enum {
	WORD,//0
	PIPE,//1
	DOUBLE,//2
	SINGLE,//3
	OPERATOR,//4
	HYPHEN,//5
	SPACE,//6
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
void	check_args(int ac, char **av, t_env **dup_env, char **env);
int	with_quotes(char *line, t_token **token, int c, int *flag);
int	take_word(char *line, t_token **token, int *flag);
int	type_token(char *content);


//*---------lst_func--------*//
t_token  *ft_lstnew_m(char *content);
t_token  *ft_lstlast_m(t_token *lst);
void    ft_lstadd_back_m(t_token **lst, t_token *new);
t_env  *ft_lstnew_env(char *key, char *value);
t_env  *ft_lstlast_env(t_env *lst);
void    ft_lstadd_back_env(t_env **lst, t_env *new);


//*---------env--------*//
void	*parse_env(char **env, t_env **dup_env);
int	get_idx_of(char *str, int c);

//*---------expand--------*//
void	handler_expand(t_token **token, t_env *env);
void	trim_quotes(t_token *token);
void	ft_minishell(t_env **env, t_token **token);
#endif