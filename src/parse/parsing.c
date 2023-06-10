/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:10:31 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_oper(t_token *token, t_redi **redir, int type)
{
	if (token)
		ft_lstadd_back_redi(redir,
			ft_lstnew_redi(ft_strdup(token->content), type));
	if (token && type == heredoc && token->type == SINGLE_EXP)
		ft_lstlast_redi(*redir)->must_exp = 1;
}

int	check_redir(t_token *token)
{
	int	len;

	len = ft_strlen(token->content) - 1;
	if (token->expand)
	{
		if (ft_strchr_2(token->content, ' ') && token->content[len] != ' ')
		{
			ft_putendl_fd_2("error in redirection", NULL, 2);
			exec.g_exit_status = 1;
			return (1);
		}
	}
	return (0);
}

void	is_operator(t_token *token, t_cmd *cmd)
{
	if (token->next)
	{
		if (check_redir(token->next))
		{
			cmd->err = 1;
			return ;
		}
	}
	if (!ft_strcmp(token->content, "<<"))
		set_oper(token->next, &cmd->in, heredoc);
	else if (*(token->content) == '<')
		set_oper(token->next, &cmd->in, in);
	else if (!ft_strcmp(token->content, ">>"))
		set_oper(token->next, &cmd->out, append);
	else if (*(token->content) == '>')
		set_oper(token->next, &cmd->out, out);
}

void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = NULL;
	while (token && token->type != PIPE)
	{
		if (token->type == OPERATOR)
		{
			is_operator(token, ft_lstlast_cmd(cmd));
			if (token && token->next)
			{
				tmp1 = token->next->next;
				ft_remove(token, &token->next, tok);
				ft_remove(tmp, &token, tok);
				token = tmp1;
			}
		}
		else
		{
			tmp = token;
			token = token->next;
		}
	}
}

void	set_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->pipe = 0;
}
