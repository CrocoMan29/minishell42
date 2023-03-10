/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:25:44 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/10 03:50:30 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize_line(t_expre *expre, char c)
{
	if (c = ' ' || c = '\t' || c = '')
}

void	get_token(char *line)
{
	t_var	*var;
	t_expre *expre;

	var->i = 0;
	while (line[var->i])
	{
		tokenize_line(&expre, line[var->i])
	}
}