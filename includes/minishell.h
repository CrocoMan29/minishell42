/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/06/17 08:41:17 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define BLUE "\e[1;36m"
# define GREEN "\e[0;92m"
# define RED "\e[0;31m"
# define RESET "\e[0m"

# define TRUE 1
# define FALSE 0

enum
{
	heredoc,
	in,
	out,
	append,
};

typedef struct s_help
{
	int				i;
	int				j;
	char			*prev;
	char			*str;
	char			*str1;
	char			*last_str;
	char			*join;
	char			*check_str;
}					t_help;

typedef struct s_redi
{
	int				type;
	char			*file;
	int				must_exp;
	struct s_redi	*next;
}					t_redi;

///////<---global struct--->///////
typedef struct s_exec
{
	int				**herdoc_pipe;
	int				**pipes;
	char			**env;
	int				built_in;
	int				std_in;
	int				std_out;
	int				g_exit_status;
	int				n_herdoc;
}					t_exec;

t_exec				g_exec;

typedef struct s_token
{
	int				type;
	char			*content;
	int				expand;
	int				check;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				valid;
	struct s_env	*next;
}					t_env;

typedef struct s_exp
{
	char			*key;
	char			*value;
	struct s_exp	*next;
}					t_exp;

///////<--command table-->///////
typedef struct s_cmd
{
	char			**cmd;
	int				pipe;
	int				err;
	int				type;
	t_redi			*in;
	t_redi			*out;
	struct s_cmd	*next;
}					t_cmd;

enum
{
	WORD,
	PIPE,
	DOUBLE,
	SINGLE,
	OPERATOR,
	HYPHEN,
	SPACEE,
	SINGLE_EXP,
};

//*----------LEXER----------*//
int					is_all_spaces(char *str);
int					token_line(char *line, t_token **token);
int					take_separator(char *line, t_token **token);
int					whish_separator(char *line);
void				check_args(int ac, char **av, t_env **dup_env, char **env);
int					with_quotes(char *line, t_token **token, int c, int *flag);
int					take_word(char *line, t_token **token, int *flag);
int					type_token(char *content);

//*---------lst_func--------*//
t_token				*ft_lstnew_m(char *content);
t_token				*ft_lstlast_m(t_token *lst);
void				ft_lstadd_back_m(t_token **lst, t_token *new);
void				ft_lstdelone_t(t_token *lst);
void				ft_lstclear_t(t_token **lst);
t_env				*ft_lstnew_env(char *key, char *value, int val);
t_env				*ft_lstlast_env(t_env *lst);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
void				ft_lstclear(t_token **lst);
void				ft_lstdelone(t_token *lst);
t_cmd				*ft_lstnew_cmd(void);
t_cmd				*ft_lstlast_cmd(t_cmd *lst);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void				clear_cmds(t_cmd **cmd);
int					ft_strchr_2(const char *str, int c);
void				ft_lstadd_back_redi(t_redi **lst, t_redi *new);
t_redi				*ft_lstnew_redi(char *out, int type);
t_redi				*ft_lstlast_redi(t_redi *lst);
void				ft_lstclear_2(t_redi **lst);

//*---------env--------*//
void				*parse_env(char **env, t_env **dup_env);
int					get_idx_of(char *str, int c);

//*---------expand--------*//
void				ft_minishell(t_env **env, t_token **token, t_cmd **cmd);
void				handler_expand(t_token **token, t_env *env, t_token *tok);
void				trim_quotes(t_token *token);
void				check_exp(t_token *tok, t_env *env);
void				hyphen_exp(t_token *tok, t_env *env);
char				*get_value_of_exp(t_env *env, char *key);
int					must_expand(int next);
int					exp_here(int curr, int next);
int					count(char *str);
void				expand_var(t_env *env, char **content);
void				expand_var_2(t_env *env, char **content, int *check);
void				here_doc_exp(t_token *token);
int					join_str(t_token **token, t_token *tmp);
void				ft_free(char **str);
void				set_type(t_token *tok);
void				ft_free_2(char *str1, char *str2, char *str3);
void	ft_free_tab2(char **arr);

//*---------checks_syntax--------*//
void				remove_spaces(t_token **token, t_token *tok);
void				ft_remove(t_token *tmp, t_token **curr, t_token **token);
int					check_syntax(t_token *token);
int					ft_putendl_fd_2(char *s, char *str, int fd);
int					find_error(t_token *token, t_token *tmp);
int					error_format(t_token *token, t_token *tmp, int i);

//*---------parsing--------*//
void				parse_cmd(t_token **token, t_cmd **cmd);
void				init_cmd(t_token **token, t_cmd **cmd);
void				rub_operator(t_cmd *cmd, t_token *token, t_token **tok);
void				is_operator(t_token *token, t_cmd *cmd);
int					check_redir(t_token *token);
void				set_oper(t_token *token, t_redi **redir, int type);
void				set_cmd(t_cmd *cmd);
void				init_args(t_token *token, t_cmd *cmd);
void				fill_cmd(t_cmd *cmd, t_token *token, int *i);

//*---------signals--------*//
void				set_signals(void);
void				sig_int_handler(int s);
void				set_default(void);
void				to_exit(void);

//*-----meharit-------execution--------------------*//

void				check_tokens(t_token *token);
void				get_input(t_cmd *command);
void				execute(t_cmd *cmd, t_env **dup_env);
int					cmd_len(char **table);
char				*ft_my_strjoin(char *s1, char const *s2);
char				*ft_my_strjoin2(char *s1, char const *s2);
int					is_builtin(char *cmd);
void				exec_builtin(char *cmd, t_cmd *table, t_env **env);
void				multi_cmd(t_env *env, t_cmd *table);
int					table_len(t_cmd *table);
void				exec_builtin(char *cmd, t_cmd *table, t_env **env);
void				which_builtin(char *cmd, t_cmd *table, t_env **env,
						int fork);
void				exec_single(t_env **env, t_cmd *table);
void				directory_error(char *dir);
void				error_cmd_not_found(char *cmd);
void				execve_error(char *cmd_path);
void				close_herdoc(t_redi *in, int i);
void				wait_all(int *pid, int last);
void				make_pipes(int **pipes);

//*-------------------cmd_exist-----------------------*//
char				**find_path(t_env *env);
void				directory_error(char *dir);
char				*directory_executable(t_cmd *table);

//*-------------------redir-----------------------*//
void				redir_in(t_cmd *table, int i);
int					redir_out(t_cmd *table);
int					open_herdoc(t_cmd *table, t_env *env);
char				*cmd_path(char **path, char *cmd);
char				*cmd_exist(t_cmd *table, t_env *env);
int					parent_herdoc(int p_id, int h);
int					is_herdoc(int herdo, int h, t_redi *tmp_in, t_env *env);
void				herdoc_child(int herdo, t_redi *tmp_in, t_env *env, int h);
int					herdoc_redir_in(t_redi *tmp_in, int h, t_env *env,
						int *herdo);
void				herdoc(int herdo, t_redi *tmp_in, t_env *env, int h);
int					n_herdoc(t_redi *in);
void				make_herdoc_pipe(int herdo, int h);
void				herdoc(int herdo, t_redi *tmp_in, t_env *env, int h);
int					n_herdoc(t_redi *in);

//*-------------------pipes------------------------*//
void				execute_cmds(t_cmd *table, t_env *env, int phase, int i);
void				wait_all(int *pid, int last);
int					n_herdoc(t_redi *in);

//*-------------------built-ins--------------------*//
void				ft_env(t_env **dup_env, int fork);
void				ft_unset(t_env **dup_env, t_cmd *cmd, int fork);
void				ft_exit(t_cmd *cmd);
void				error_mess_exit(char *str);
void				ft_pwd(t_env *env, int fork);
void				ft_cd(t_cmd *cmd, t_env **env, int fork);
char				*get_pwd(t_env *env);
char				*get_home(t_env *env);
void				ft_echo(t_cmd *cmd, int fork);
void				ft_export(t_env *dup_env, t_cmd *table, int fork);
void				unset_var(t_env *env, int index, t_env **head);
void				env_i(t_env **dup_env);
char				*get_pwd(t_env *env);
int					my_ft_atoi(const char *str);
void				error_mess_exp(char *cmd);
int					does_exist(char *key, t_env *dup_env);
int					valid_ident(char *ident);
int					env_valid(char *ident);
void				add_to(char *key, char *value, t_env *dup_env, char *ident);
void				error_mess_uns(char *cmd);

int					my_strchr(char *str, char c);
char				*my_ft_strdup(const char *s1);

void				minishell_mess(void);
void				rl_replace_line(const char *str, int state);


void    get_input(t_cmd *command);

#endif
