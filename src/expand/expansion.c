/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 01:54:37 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/03 09:48:12 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_quotes(t_token *token)
{
	char *tmp;
	t_token *temp;
	temp = token;
	
	// while (token)
	// {
	// 	printf("-|%s|-", token->content);
	// 	token = token->next;
	// }
	//TODOfree previous token
	while (token)
	{
		tmp = token->content;
		if (!*tmp)
		{
			token->content = ft_strdup("");
			free(tmp);
		}
		if (token->type == 2)
		{
			token->content = ft_strtrim(token->content, "\"");
			free(tmp);
			// printf("-|%s|-", token->content);
		}
		if (token->type == 3)
		{
			token->content = ft_strtrim(token->content, "\'");
			free(tmp);
		}
		token = token->next;
	}
	// printf("\n");
	while (temp)
	{
		printf("-|%s|-", temp->content);
		temp = temp->next;
	}
	printf("\n");
	// printf("HELLO\n");
}

void	handler_expand(t_token **token, t_env *env)
{
	t_token *tmp;
	
	tmp = NULL;
	(void)env;
	trim_quotes(*token);
	// while (*token)
	// {
	// 	printf("-|%s|-", token->content);
	// 	token = *token->next;
	// }
}