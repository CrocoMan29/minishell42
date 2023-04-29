/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 00:05:30 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/29 02:06:33 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_format(t_token *token, t_token *tmp, int i)
{
	if (i)
	{
		if (tmp->type == OPERATOR && token->type == OPERATOR)
			return (ft_putendl_fd_2("syntax error near unexpected token", token->content, 2));
		if (tmp->type == OPERATOR && token->type == PIPE)
			return (ft_putendl_fd_2("syntax error near unexpected token", token->content, 2));
		if (tmp->type == PIPE && token->type == PIPE)
			return (ft_putendl_fd_2("syntax error near unexpected token", token->content, 2));
		if (tmp->type == PIPE && token->type == OPERATOR && (!token->next || token->next->type == OPERATOR || token->next->type == PIPE))
			return (ft_putendl_fd_2("syntax error near unexpected token", token->content, 2));
	}
	return (1);
}

int	find_error(t_token *token, t_token *tmp)
{
	if ((tmp->type == PIPE || tmp->type == OPERATOR) && (token->type == PIPE || token->type == OPERATOR))
	{
		if (!error_format(token, tmp, 1))
			return (0);
	}
	return (1);
}

int	check_syntax(t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token && token->type == PIPE)
		return (ft_putendl_fd_2("syntax error near unexpected token", "|", 2));
	if (token && !token->next && (token->type == OPERATOR || token->type == PIPE))
		return (ft_putendl_fd_2("syntax error near unexpected token", "newline", 2));
	while(token)
	{
		if ((!ft_strcmp(token->content, "&&") || !ft_strcmp(token->content, "&")) && token->type == WORD)
			return (ft_putendl_fd_2("syntax error asat", "haha", 2));
		if (tmp && !find_error(token, tmp))
			return (0);
		tmp = token;
		token = token->next;
	}
	if (tmp && (tmp->type == OPERATOR || tmp->type == PIPE))
		return (ft_putendl_fd_2("syntax error near unexpected token", "newline", 2));
	return (1);
}
