/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:54:37 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/08 07:40:23 by yismaail         ###   ########.fr       */
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
	// printf("%d\n",token->type);
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
		// printf ("yassir");
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
	// printf("<<<<<<<%s\n", *content);
	i = 0;
	while (prev[i] && !exp_here(prev[i], prev[i + 1]))
		i++;
	if (!prev[i])
		return ;
	if (i)
		str = ft_substr(prev, 0, i);
	j = i + 1 + count(prev + i + 1);
	str1 = get_value_of_exp(env, ft_substr(prev, i + 1, j - i -1));
	// printf ("%d\n", j);
	join = ft_strjoin(str, str1);
	printf ("<<<<%s\n", join);
	if (ft_strlen(prev + j))
		last_str = ft_substr(prev, j, ft_strlen(prev + j));
	printf (">>>>>%s\n", last_str);
	*content = ft_strjoin(join, last_str);
	// printf("-----%s\n", *content);
	// printf ("%s\n", *content);
	// if (!last_str)
	// 	free(join);
	
	// if (last_str)
	// 	free(last_str);
	// free(str1);
	// free(prev);
	// free(str);
	// free(str1);
	// free(join);
	// free(last_str);
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
		printf ("%s\n",tok->content);
		expand_var(env, &tok->content);
		printf ("%s\n",tok->content);
		// printf ("643135454");
		// printf ("Yassir\n");
	}
}

void	handler_expand(t_token **token, t_env *env, t_token *tok)
{
	t_token *tmp;
	
	tmp = NULL;
	(void)env;
	(void)tok;
	trim_quotes(*token);
	
	while (tok)
	{
		check_exp(tok, env);
		tok = tok->next;
	}
	// printf ("\n");
	
}