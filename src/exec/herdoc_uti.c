/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_uti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:08:38 by meharit           #+#    #+#             */
/*   Updated: 2023/06/13 22:46:19 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	herdoc(int herdo, t_redi *tmp_in, t_env *env, int h)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || !ft_strcmp(line, tmp_in->file))
		{
			free(line);
			break ;
		}
		if (herdo == 1)
		{
			if (tmp_in->must_exp)
				expand_var(env, &line);
			write(g_exec.herdoc_pipe[h][1], line, ft_strlen(line));
			write(g_exec.herdoc_pipe[h][1], "\n", 1);
		}
		free(line);
	}
}

int	n_herdoc(t_redi *in)
{
	int	n;

	n = 0;
	while (in)
	{
		if (in->type == heredoc)
			n++;
		in = in->next;
	}
	g_exec.n_herdoc = n;
	return (n);
}
