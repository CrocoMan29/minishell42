/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:25:44 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/03 00:46:51 by yismaail         ###   ########.fr       */
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

int	type_token(char *content)
{
	// printf("%s <<\n", content);
	// exit(0);
	if (*content == '\'')
		return (SINGLE);
	if (*content == '\"')
		return (DOUBLE);
	if (*content == '|')
		return (PIPE);
	if (content[0] && content[1] && !ft_strncmp(content, "<<", 2))
		return (OPERATOR);
	if (content[0] && content[1] && !ft_strncmp(content, ">>", 2))
		return (OPERATOR);
	if (*content == '<' || *content == '>')
		return (OPERATOR);
	if (*content == '~' && ft_strlen(content) == 1)
		return (HYPHEN);
	if (*content == ' ')
		return (SPACE);
	else
		return (WORD);
}

int	take_separator(char *line, t_token **token, int *done)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 12) || line[i] == 32))
		i++;
	if (i && *token)
	{
		*done = 1;
		ft_lstadd_back_m(token, ft_lstnew_m(ft_strdup(" ")));
	}
	if (whish_separator(line + i) == 1)
	{
		*done = 1;
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 1)));
		return (i + 1);
	}
	if (whish_separator(line + i) == 3)
	{
		*done = 1;
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line + i, 0, 2)));
		return (i + 2);
	}
	return (i);
	
}

int	with_quotes(char *line, t_token **token, int c, int *flag, int *done)
{
	int	i;

	i = 1;
	while (line [i] && line[i] != c)
		i++;
	if (line[i] != c)
	{
		ft_putstr_fd("eroooor11", 2);
		*flag = 0;
		return (0);
	}
	if (i)
	{
		*done = 1;
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i + 1)));
	}
	return (i + 1);
}

int	take_word(char *line, t_token **token, int *flag, int *done)
{
	int	i;

	i = 0;
	if (line[i] == '\'' || line[i] == '\"')
		return (with_quotes(line, token, *line, flag, done));
	if (whish_separator(line + i))
		return (0);
	while (line[i] && !whish_separator(line + i) && line[i] != '\'' && line[i] != '\"')
		i++;
	if (i)
	{
		*done = 1;
		ft_lstadd_back_m(token, ft_lstnew_m(ft_substr(line, 0, i)));
	}
	return (i);
}

int	token_line(char *line, t_token **token)
{
	int	i;
	int	flag;
	int	done;
	
	i = 0;
	flag = 1;
	while (line[i])
	{
		done = 0;
		i += take_separator(line + i, token, &done);
		i += take_word(line + i, token, &flag, &done);
		if (!flag)
		{
			ft_lstclear_t(token);
			write(2, "token line error", 16);
			return (0);
		}
		if (done == 0)
			i++;
	}
	check_tokens(*token);
	printf("*******************************");
	return (1);
}
