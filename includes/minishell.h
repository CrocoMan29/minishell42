/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/01 16:54:33 by meharit          ###   ########.fr       */
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
// char	**g_env;

#define BLUE "\e[1;36m"
# define GREEN "\e[0;92m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

enum {
	heredoc,
	in,
	out,
	append,
};


typedef struct s_redi
{
	int				type;
	char			*file;
	int				must_exp;
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
	int		valid;
	struct s_env	*next;
}					t_env;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
}					t_exp;

typedef struct s_cmd
{
	char			**cmd;
	int				pipe;
	int				err;
	t_redi			*in;
	t_redi			*out;
	struct s_cmd	*next;
}					t_cmd;

enum {
	WORD,//0
	PIPE,//1
	DOUBLE,//2
	SINGLE,//3
	OPERATOR,//4
	HYPHEN,//5
	SPACE,//6
	SINGLE_EXP,//7
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
t_token	*ft_lstnew_m(char *content);
t_token	*ft_lstlast_m(t_token *lst);
void    ft_lstadd_back_m(t_token **lst, t_token *new);
void	ft_lstdelone_t(t_token *lst);
void	ft_lstclear_t(t_token **lst);
t_env	*ft_lstnew_env(char *key, char *value, int val);
t_env	*ft_lstlast_env(t_env *lst);
void    ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_lstclear(t_token **lst);
void	ft_lstdelone(t_token *lst);
t_cmd	*ft_lstnew_cmd(void);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void    ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int		ft_strchr_2(const char *str, int c);
void	ft_lstadd_back_redi(t_redi **lst, t_redi *new);
t_redi	*ft_lstnew_redi(char *out, int type);
t_redi	*ft_lstlast_redi(t_redi *lst);


//*---------env--------*//
void	*parse_env(char **env, t_env **dup_env);
int	get_idx_of(char *str, int c);

//*---------expand--------*//
void	ft_minishell(t_env **env, t_token **token, t_cmd **cmd);
void	handler_expand(t_token **token, t_env *env, t_token *tok);
void	trim_quotes(t_token *token);
void	check_exp(t_token *tok, t_env *env);
void	hyphen_exp(t_token *tok, t_env *env);
char	*get_value_of_exp(t_env *env, char *key);
int	must_expand(int next);
int	exp_here(int curr, int next);
int	count(char *str);
void	expand_var(t_env *env, char **content);
void	here_doc_exp(t_token *token);
int	join_str(t_token **token, t_token *tmp);


//*---------checks_syntax--------*//
void	remove_spaces(t_token **token, t_token *tok);
void	ft_remove(t_token *tmp, t_token **curr, t_token **token);
int		check_syntax(t_token *token);
int		ft_putendl_fd_2(char *s, char *str, int fd);
int		find_error(t_token *token, t_token *tmp);
int		error_format(t_token *token, t_token *tmp, int i);

//*---------parsing--------*//
void	parse_cmd(t_token **token, t_cmd **cmd);
void	init_cmd(t_token **token, t_cmd **cmd);
void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok);
void	is_operator(t_token *token, t_cmd *cmd);
int		check_redir(t_token *token);
void	set_oper(t_token *token, t_redi **redir, int type);
void	set_cmd(t_cmd *cmd);
void	init_args(t_token *token, t_cmd *cmd);
void	fill_cmd(t_cmd *cmd, t_token *token, int *i);

//*-----meharit-------execution--------------------*//

void    check_tokens(t_token *token);
void    get_input(t_cmd *command);
void	execute(t_cmd *cmd, t_env **dup_env);
int		cmd_len(char **table);

//*-------------------built-ins--------------------*//
void	ft_env(t_env **dup_env);
void	ft_unset(t_env **dup_env, t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_pwd(void);
void	ft_cd(t_cmd *cmd, t_env **env);
void	ft_echo(t_cmd *cmd);
void	ft_export(t_env *dup_env, t_cmd *table);
void    unset_var(t_env *env, int index, t_env **head);

#endif
