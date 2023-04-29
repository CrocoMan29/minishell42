/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:10:31 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/29 02:40:11 by yismaail         ###   ########.fr       */
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
	else if (*(token->content) == '>')
		set_oper(token->next, &cmd->out, out);
	else if (!ft_strcmp(token->content, ">>"))
		set_oper(token->next, &cmd->out, append);
}

void	rub_operator(t_cmd *cmd, t_token *token, t_token **tok)
{
	t_token	*tmp;
	t_token	*tmp1;

	tmp = NULL;
	while(token && token->type != PIPE)
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

void	init_args(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOUBLE || token->type == SINGLE || token->type == HYPHEN)
			i++;
		token = token->next;
	}
	if (!i++)
		return ;
	cmd->cmd = malloc(i * sizeof(char *));
	if (!cmd->cmd)
		return ;
	cmd->cmd[--i] = NULL;
}

void	init_cmd(t_token **token, t_cmd **cmd)
{
	ft_lstadd_back_cmd(cmd, ft_lstnew_cmd());
	set_cmd(ft_lstlast_cmd(*cmd));
	rub_operator(*cmd, *token, token);
	init_args(*token, ft_lstlast_cmd(*cmd));
}

void	fill_cmd(t_cmd *cmd, t_token *token, int *i)
{
	if (!token || token->type == SPACE)
		return ;
	if ((token->type == WORD || token->type == HYPHEN || token->type == SINGLE || token->type == DOUBLE) && cmd->cmd)
		cmd->cmd[(*i)++] = ft_strdup(token->content);
	else if (*(token->content) == '|')
	{
		if (token->next && token->next->content)
			cmd->pipe = 1;
	}
}

void	parse_cmd(t_token **token, t_cmd **cmd)
{
	t_token *tmp;
	t_token	*tmp1;
	int		i;
	static int p;

	init_cmd(token, cmd);
	if (p && !ft_lstlast_cmd(*cmd)->in)
		ft_lstlast_cmd(*cmd)->pipe = p--;
	i = 0;
	tmp = *token;
	while (tmp && tmp->type != PIPE)
	{
		tmp1 = tmp;
		fill_cmd(ft_lstlast_cmd(*cmd), tmp, &i);
		tmp = tmp->next;
		ft_lstdelone_t(tmp1);
	}
	if (!tmp)
		return ;
	*token = tmp->next;
	fill_cmd(ft_lstlast_cmd(*cmd), tmp, &i);
	ft_lstdelone_t(tmp);
	if (ft_lstlast_cmd(*cmd)->pipe)
		p++;
	return(parse_cmd(token, cmd));
}
