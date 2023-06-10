/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:45:07 by meharit           #+#    #+#             */
/*   Updated: 2023/06/09 20:38:40 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	make_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			perror("pipe");
		i++;
	}
}

void	wait_all(int *pid, int last) //recheck it
{
	int	i;
	int	status;

	i = 0;
	close(exec.pipes[1][0]);
	close(exec.pipes[1][1]);
	close(exec.pipes[0][1]);
	close(exec.pipes[0][0]);

	waitpid(pid[last - 1], &status, 0);
	if (WIFEXITED(status))
		exec.g_exit_status = WEXITSTATUS(status);

	while (i < last - 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

void	open_uno(int i)
{
	if (i % 2 == 0)
		pipe(exec.pipes[1]);
	else
		pipe(exec.pipes[0]);
}

void	multi_cmd(t_env *env, t_cmd *table)
{
	int	i;
	int	tbl_len;
	int	*f_pid;
	
	i = 0;
	tbl_len = table_len(table);
	exec.pipes = (int **)malloc(sizeof(int *) * 2);
	make_pipes(exec.pipes);
	f_pid = (int *)malloc(sizeof(int) * tbl_len);
	while (table)
	{
		f_pid[i] = fork();
		if (f_pid[i] == 0) // child proc
		{
			if (i == 0)
				execute_cmds(table, env, 0, i);
				
			else if (i == tbl_len - 1)
				execute_cmds(table, env, 2, i);
				
			else
				execute_cmds(table, env, 1, i);
		}
		// back to parent
		else
		{
			if (i == 0)
			{
				close(exec.pipes[1][0]);
				close(exec.pipes[1][1]);
				close(exec.pipes[0][1]);
			}
			else if (i == tbl_len - 1)
			{
				close(exec.pipes[0][0]);
				close(exec.pipes[1][0]);
				close(exec.pipes[1][1]);
				close(exec.pipes[0][1]);
			}
			else if (i % 2 == 0)
			{
				
				close(exec.pipes[0][1]);
				close(exec.pipes[1][0]);
				close(exec.pipes[1][1]);
			}
			else //i % 2 != 0
			{
				close(exec.pipes[0][0]);
				close(exec.pipes[1][1]);
			}
			// if (exec.n_herdoc)
			// 	close(exec.herdoc_pipe[i][0]);
			open_uno(i);
		}
		table = table->next;
		i++;	
	}
	wait_all(f_pid, i);
	free(exec.pipes[0]);
	free(exec.pipes[1]);
	free (exec.pipes);
	free (f_pid);
}
