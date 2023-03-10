/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 23:03:54 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/10 02:47:37 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct s_token
{
	int	type;
	char	*value;
}		t_token;

typedef struct s_expre
{
	char	*str;
	struct s_expre *next;
	struct t_token *token;
}	t_expre;

typedef struct s_var
{
	int	i;
	int j;
}		t_var;

enum {
	TOKEN_WORD,
	TOKEN_CMD,
	TOKEN_INFILE,
	TOKEN_OUTFILE,
	TOKEN_REDIR,
};

void	ft_minishell(char **env);
void	get_token(char *line);

#endif