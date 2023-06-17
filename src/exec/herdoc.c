/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 14:13:03 by meharit           #+#    #+#             */
/*   Updated: 2023/06/13 22:47:48 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parent_herdoc(int p_id, int h)
{
	int	status;

	waitpid(p_id, &status, 0);
	if (WIFSIGNALED(status))
	{
		free(g_exec.herdoc_pipe[h]);
		g_exec.g_exit_status = WTERMSIG(status) + 128;
		return (1);
	}
	return (0);
}

int	is_herdoc(int herdo, int h, t_redi *tmp_in, t_env *env)
{
	int	p_id;

	p_id = fork();
	if (!p_id)
	{
		set_default();
		herdoc(herdo, tmp_in, env, h);
		if (!herdo)
			close(g_exec.herdoc_pipe[h][1]);
		exit(g_exec.g_exit_status);
	}
	else
	{
		herdo--;
		if (parent_herdoc(p_id, h))
			return (1);
	}
	return (0);
}

void	herdoc_child(int herdo, t_redi *tmp_in, t_env *env, int h)
{
	set_default();
	herdoc(herdo, tmp_in, env, h);
	if (!herdo)
		close(g_exec.herdoc_pipe[h][1]);
	exit(g_exec.g_exit_status);
}

int	herdoc_redir_in(t_redi *tmp_in, int h, t_env *env, int *herdo)
{
	int	p_id;

	if (tmp_in->type == heredoc)
	{
		p_id = fork();
		if (!p_id)
			herdoc_child(*herdo, tmp_in, env, h);
		else
		{
			(*herdo)--;
			if (parent_herdoc(p_id, h))
				return (1);
		}
	}
	return (0);
}

void	make_herdoc_pipe(int herdo, int h)
{
	if (herdo)
	{
		g_exec.herdoc_pipe[h] = malloc(sizeof(t_exec) * 2);
		if (pipe(g_exec.herdoc_pipe[h]) == -1)
			perror("pipe\n");
	}
}
