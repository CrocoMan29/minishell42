/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:51:26 by meharit           #+#    #+#             */
/*   Updated: 2023/06/13 22:48:25 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	table_len(t_cmd *table)
{
	int	len;

	len = 0;
	while (table)
	{
		table = table->next;
		len++;
	}
	return (len);
}

int	single_parent_proc(int f_pid)
{
	int	status;

	if (g_exec.n_herdoc)
	{
		close(g_exec.herdoc_pipe[0][0]);
		close(g_exec.herdoc_pipe[0][1]);
		free(g_exec.herdoc_pipe[0]);
	}
	waitpid(f_pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		g_exec.g_exit_status = WTERMSIG(status) + 128;
		return (1);
	}
	g_exec.g_exit_status = WEXITSTATUS(status);
	return (0);
}

void	single_child_proc(t_env **env, t_cmd *table)
{
	char	*cmd_path;

	set_default();
	cmd_path = cmd_exist(table, *env);
	redir_in(table, 0);
	redir_out(table);
	if (table->cmd)
	{
		if (!cmd_path || !table->cmd[0][0])
		{
			if (opendir(table->cmd[0]))
				directory_error(table->cmd[0]);
			error_cmd_not_found(table->cmd[0]);
		}
		if (execve(cmd_path, table->cmd, g_exec.env) == -1)
			execve_error(cmd_path);
	}
	else
		exit(0);
}

void	execve_error(char *cmd_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_path, 2);
	perror(" ");
	g_exec.g_exit_status = 126;
	exit(g_exec.g_exit_status);
}

void	exec_single(t_env **env, t_cmd *table)
{
	int	f_pid;

	if (table->cmd && is_builtin(table->cmd[0]))
		exec_builtin(table->cmd[0], table, env);
	else
	{
		f_pid = fork();
		if (!f_pid)
			single_child_proc(env, table);
		else
		{
			if (single_parent_proc(f_pid))
				return ;
		}
	}
}
