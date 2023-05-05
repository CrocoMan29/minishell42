/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:54:37 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/30 13:56:13 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_quotes(t_token *token)
{
	char *tmp;
	t_token *temp;
	temp = token;

	// //TODOfree previous token
	while (token)
	{
		tmp = token->content;
		if (!*tmp)
		{
			free(tmp);
			token->content = ft_strdup("");
			return ;
		}
		if (token->type == 2)
		{
			token->content = ft_strtrim(token->content, "\"");
			free(tmp);
		}
		if (token->type == 3)
		{
			token->content = ft_strtrim(token->content, "\'");
			free(tmp);
		}
		token = token->next;
	}
}

char	*get_value_of_exp(t_env *env, char *key)
{
	while (env && ft_strcmp(env->key, key) != 0)
		env = env->next;
	if (env && ft_strcmp(env->key, key) == 0)
	{
		free(key);
		return (ft_strdup(env->value));
	}
	free(key);
	return (ft_strdup(""));
}

void	hyphen_exp(t_token *tok, t_env *env)
{
	char	*tmp;

	if (tok)
	{
		tmp = tok->content;
		tok->content = get_value_of_exp(env, ft_strdup("HOME"));
		free(tmp); 
	}
}

int	must_expand(int next)
{
	if (!ft_isalnum(next) && next != '_')
		return (1);
	return (0);
}

int	exp_here(int curr, int next)
{
	if (curr == '$' && next == '?')
		return (1);
	if (curr == '$' && !must_expand(next))
		return (1);
	return (0);
}

int	count(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while (str[i] && !must_expand(str[i]))
		i++;
	return (i);
}

void	expand_var(t_env *env, char **content)
{
	int	i;
	int	j;
	char	*prev;
	char	*str;
	char	*str1;
	char	*last_str;
	char	*join;

	str = NULL;
	str1 = NULL;
	join = NULL;
	last_str = NULL;
	prev = *content;
	i = 0;
	while (prev[i] && !exp_here(prev[i], prev[i + 1]))
		i++;
	if (!prev[i] || !prev[i + 1])
		return ;
	if (i)
		str = ft_substr(prev, 0, i);
	j = i + 1 + count(prev + i + 1);
	str1 = get_value_of_exp(env, ft_substr(prev, i + 1, j - i -1));
	join = ft_strjoin(str, str1);
	if (ft_strlen(prev + j))
		last_str = ft_substr(prev, j, ft_strlen(prev + j));
	*content = ft_strjoin(join, last_str);
	if (!last_str)
		free(join);
	if (last_str)
		free(last_str);
	free(prev);
	free(str1);
	expand_var(env, content);
}

void	check_exp(t_token *tok, t_env *env)
{
	(void)env;

	if (tok->type == HYPHEN)
	{
		hyphen_exp(tok, env);
		printf("%s\n", tok->content);
	}
	else if ((tok->type == DOUBLE || tok->type == WORD) && ft_strlen(tok->content) > 1)
	{
		if (*(tok->content) == '$')
			tok->expand = 1;
		expand_var(env, &tok->content);
	}
}

void	here_doc_exp(t_token *token)
{
	while (token)
	{
		if (*token->content == '$' && ft_strlen(token->content) == 1)
		{
			if (token->next && (token->next->type == DOUBLE || token->next->type == SINGLE))
			{
				token->content = ft_strdup("");
				// printf("%s", token->content);
			}
		}
		else if (ft_strlen(token->content) == 2 && token->type == OPERATOR && ft_strcmp(token->content, "<<") == 0)
		{
			if (token->next && token->next->type == SPACE)
			{
				if (token->next->next && token->next->next->type != PIPE && token->next->next->type != OPERATOR)
				{
					if (token->next->next->type == WORD)
						token->next->next->type = SINGLE_EXP;
					else
						token->next->next->type = SINGLE;
				}
			}
			else if (token->next && token->next->type != PIPE && token->next->type != OPERATOR)
			{
				if (token->next->type == WORD)
					token->next->type = SINGLE_EXP;
				else
					token->next->type = SINGLE;
			}
		}
		token = token->next;
	}
}

int	join_str(t_token **token, t_token *tmp)
{
	if ((*token)->type == PIPE || (*token)->type == OPERATOR || (*token)->type == SPACE || (*token)->type == WORD || (*token)->type == DOUBLE || (*token)->type == SINGLE)
		return (0);
	if (!tmp || tmp->type == PIPE || tmp->type == OPERATOR)
		return (0);
	else
	{
		tmp->content = ft_strjoin(tmp->content, (*token)->content);
		// printf("%s\n", (*token)->content);
		tmp->next = (*token)->next;
		ft_lstdelone_t(*token);
		*token = tmp->next;
		return (1);
	}
}

void	handler_expand(t_token **token, t_env *env, t_token *tok)
{
	t_token *tmp;
	
	tmp = NULL;
	(void)env;
	(void)tok;
	trim_quotes(*token);
	here_doc_exp(*token);
	while (tok)
	{
		check_exp(tok, env);
		
		// printf("%s\n", tok->content);
		if (join_str(&tok, tmp) == 0)
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}
