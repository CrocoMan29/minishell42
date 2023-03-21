/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:25:44 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/20 15:20:05 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	whish_separator(char *line)
{
	if (*line == '|')
		return (1);
	if (*line == 32 || (*line >= 9 && *line <= 12))
		return (2);
	if (!ft_strncmp(line, "<<", 2) || !ft_strncmp(line, ">>", 2))
		return (3);
	if (*line == '<' || *line == '>')
		return (1);
	return (0);
}

int	take_separator(char *line, t_token **token)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 12) || line[i] == 32))
		i++;
	if (i && *token)
		ft_lstadd_back_m(token, ft_lstnew_m(ft_strdup(" ")));
	if (whish_separator(line + i) == 1)
	{
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 1)));
		return (i +1);
	}
	if (whish_separator(line + i) == 3)
	{
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 2)));
		return (i + 2);
	}
	return (i);
	
}

// int	take_word(char *line, t_token **token, int *flag)
// {
// 	int	i;

// 	i = 0;
// 	if (line[i] == '\'' || line[i] == '\"')
// 		return ()
// }

int	with_quotes(char *line, t_token **token, int flag)
{
	int	i;

	i = 0;
	if (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'' || line[i] != '\"')
				i++;
			if (line[i] == '\'')
				ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i)));
			else
			{
				flag = 0;
				return (flag);
			}
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && (line[i] != '\'' || line[i] != '\"'))
				i++;
			printf ("FIRST i => %d \n", i);
			if (line[i] == '\"')
				ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i)));
			else
			{
				flag = 0;
				return (flag);	
			}
		}
	}
	return (i);
}

int	take_word(char *line, t_token **token, int *flag)
{
	int	i;

	i = 0;
	if (*line == '\'' || *line == '\"')
		return (with_quotes(line, token, *flag));
	while (line[i] && !whish_separator(line + i))
		i++;
	ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i)));
	return (i);
}

int	token_line(char *line, t_token **token)
{
	int	i;
	int	flag;
	
	i = 0;
	flag = 1;
	while (line[i])
	{
		i += take_separator(line + i, token);
		i += take_word(line + i, token, &flag);
		if (flag == 0)
			return (0);
		i++;
	}
	
	return (1);
}