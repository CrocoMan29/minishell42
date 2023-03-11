/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 02:25:44 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/11 02:53:31 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	take_token(t_var var, t_expre *expre, char *line)
{
	while (line[var.i])
	{
		if (whitespace(line[var.i]) == 1)
			var.i++;
		if (special_char(line[var.i]) == 1)
		{
			
		}
	}
}

void	get_token(char *line)
{
	t_var	*var;
	t_expre *expre;

	take_token(var, expre, line);
}