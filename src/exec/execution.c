/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:02:22 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 22:00:53 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute(t_cmd *table, t_env **dup_env)
{
	if (table)
	{
		g_exec.herdoc_pipe = malloc(sizeof(t_exec) * table_len(table));
		if (!table)
			return ;
		if (open_herdoc(table, *dup_env))
			return ;
		if (table_len(table) == 1)
			exec_single(dup_env, table);
		else
			multi_cmd(*dup_env, table);
		free(g_exec.herdoc_pipe);
	}
}
