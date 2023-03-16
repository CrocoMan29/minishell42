/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:25:44 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/16 09:41:15 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	depacer_separator(char *line, t_token **token)
{
	int	i;

	i = 0;
	while (line[i] && ((line[i] >= 9 && line[i] <= 12) || line[i] == 32))
		i++;
	
}

int	token_line(char *line, t_token **token)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		// i += depacer_separator(line + i, token);
		while ((line[i] >= 9 && line[i] <= 12) || line[i] == 32)
			i++;
		if (line[i] != )
	}
	return (1);
}