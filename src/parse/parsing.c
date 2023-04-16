/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:10:31 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/16 03:10:33 by yismaail         ###   ########.fr       */
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

	len = ft_strlen(token->content);
	if (token->expand)
	{
		if (ft_strchr_2(token->content, ' ') && token->content[len] != 'n')
		{
			ft_putendl_fd_2("error in redirection", NULL, 2);
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
	if (!ft_strcmp(token->content, "<"))
		set_oper(token->next, &cmd->in, in);
	if (!ft_strcmp(token->content, ">"))
		set_oper(token->next, &cmd->out, out);
	if (!ft_strcmp(token->content, ">>"))
		set_oper(token->next, &cmd->out, append);
}

void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok)
{
	t_token	*tmp;

	(void)tok;
	tmp = NULL;
	while(token && token->type != PIPE)
	{
		if (token->type == OPERATOR)
		{
			is_operator(token, ft_lstlast_cmd(cmd));
			while(cmd)
			{
				printf ("%s\n", cmd->in->file);
				cmd = cmd->next;
			}
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

void	init_cmd(t_token **token, t_cmd **cmd)
{
	ft_lstadd_back_cmd(cmd, ft_lstnew_cmd());
	set_cmd(ft_lstlast_cmd(*cmd));
	rub_operator(*cmd, *token, token);
}

void	parse_cmd(t_token **token, t_cmd **cmd)
{
	init_cmd(token, cmd);
}
