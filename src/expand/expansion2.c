/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 07:20:45 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/31 17:41:30 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exp(t_token *tok, t_env *env)
{
	(void)env;
	if (tok->type == HYPHEN)
	{
		hyphen_exp(tok, env);
		printf("%s\n", tok->content);
	}
	else if ((tok->type == DOUBLE || tok->type == WORD)
		&& ft_strlen(tok->content) > 1)
	{
		if (*(tok->content) == '$')
			tok->expand = 1;
		expand_var(env, &tok->content);
	}
}

void	set_type(t_token *tok)
{
	if (tok->type == WORD)
		tok->type = SINGLE_EXP;
	else
		tok->type = SINGLE;
}

void	here_doc_exp(t_token *token)
{
	while (token)
	{
		if (*token->content == '$' && ft_strlen(token->content) == 1)
		{
			if (token->next && (token->next->type == DOUBLE
					|| token->next->type == SINGLE))
				token->content = ft_strdup("");
		}
		else if (ft_strlen(token->content) == 2 && token->type == OPERATOR
			&& ft_strcmp(token->content, "<<") == 0)
		{
			if (token->next && token->next->type == SPACEE)
			{
				if (token->next->next && token->next->next->type != PIPE
					&& token->next->next->type != OPERATOR)
					set_type(token->next->next);
			}
			else if (token->next && token->next->type != PIPE
				&& token->next->type != OPERATOR)
				set_type(token->next);
		}
		token = token->next;
	}
}

int	join_str(t_token **token, t_token *tmp)
{
	if ((*token)->type == PIPE || (*token)->type == OPERATOR
		|| (*token)->type == SPACEE)
		return (0);
	if (!tmp || tmp->type == PIPE || tmp->type == OPERATOR
		|| tmp->type == SPACEE)
		return (0);
	else
	{
		tmp->content = ft_strjoin(tmp->content, (*token)->content);
		tmp->next = (*token)->next;
		ft_lstdelone_t(*token);
		*token = tmp->next;
		return (1);
	}
}

void	handler_expand(t_token **token, t_env *env, t_token *tok)
{
	t_token	*tmp;

	(void)env;
	(void)token;
	tmp = NULL;
	trim_quotes(*token);
	here_doc_exp(*token);
	while (tok)
	{
		check_exp(tok, env);
		if (join_str(&tok, tmp) == 0)
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}
