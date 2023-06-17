/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:32:33 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 00:16:59 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes_child(void)
{
	close(g_exec.pipes[1][1]);
	close(g_exec.pipes[0][0]);
	close(g_exec.pipes[0][1]);
	close(g_exec.pipes[1][0]);
}

void	dup_it(int phase, int i)
{
	if (phase == 0)
		dup2(g_exec.pipes[0][1], 1);
	if (i % 2 == 0)
	{
		if (phase == 1)
		{
			dup2(g_exec.pipes[0][1], 1);
			dup2(g_exec.pipes[1][0], 0);
		}
		if (phase == 2)
			dup2(g_exec.pipes[1][0], 0);
	}
	else
	{
		if (phase == 1)
		{
			dup2(g_exec.pipes[1][1], 1);
			dup2(g_exec.pipes[0][0], 0);
		}
		if (phase == 2)
			dup2(g_exec.pipes[0][0], 0);
	}
	close_pipes_child();
}

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exec.g_exit_status = 127;
	exit(g_exec.g_exit_status);
}

void	execute_cmds(t_cmd *table, t_env *env, int phase, int i)
{
	char	*cmd_path;
	char	*cmd;

	cmd_path = cmd_exist(table, env);
	dup_it(phase, i);
	redir_in(table, i);
	redir_out(table);
	if (table->cmd)
	{
		cmd = table->cmd[0];
		if (is_builtin(cmd))
			which_builtin(cmd, table, &env, TRUE);
		if (!cmd_path)
			error_cmd_not_found(cmd);
		if (execve(cmd_path, table->cmd, g_exec.env) == -1)
		{
			perror("");
			g_exec.g_exit_status = 126;
		}
	}
	exit(g_exec.g_exit_status);
}
