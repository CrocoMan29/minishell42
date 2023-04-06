/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:54:37 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/06 02:54:07 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_quotes(t_token *token)
{
	char *tmp;
	t_token *temp;
	temp = token;

	//TODOfree previous token
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
	// // printf("\n");
	// while (temp)
	// {
	// 	printf("-|%s|-", temp->content);
	// 	temp = temp->next;
	// }
	// printf("\n");
	// printf("HELLO\n");
}

char	*get_value_of_exp(t_env env, char *key)
{
	while (env && ft_strcmp(env.key, key) != 0)
		i++;
	if (env && ft_strcmp(env.key, key) == 0)
	{
		free(key);
		return (ft_strdup(env.value));
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
		tok->content = get_value_of_exp(env, env.key);
		free(tmp); 
	}
}

void	check_exp(t_token *tok, t_env *env)
{
	(void)env;

	if (tok->type == HYPHEN)
	{
		hyphen_exp(tok, env);
	}
	// if (*(tok->content) == '$')
	// {
	// 	printf("%c\n", *(tok->content));
	// 	printf("oki\n");
	// }
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