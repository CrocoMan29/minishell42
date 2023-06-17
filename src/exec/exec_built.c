/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:47:29 by meharit           #+#    #+#             */
/*   Updated: 2023/06/13 17:16:58 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "export"))
		return (1);
	return (0);
}

void	exec_builtin(char *cmd, t_cmd *table, t_env **env)
{
	g_exec.std_in = dup(STDIN_FILENO);
	g_exec.std_out = dup(STDOUT_FILENO);
	g_exec.built_in = 1;
	redir_in(table, 0);
	redir_out(table);
	which_builtin(cmd, table, env, FALSE);
	dup2(g_exec.std_in, STDIN_FILENO);
	dup2(g_exec.std_out, STDOUT_FILENO);
	close(g_exec.std_in);
	close(g_exec.std_out);
	g_exec.built_in = 0;
}

void	exit_env_pwd(char *cmd, t_cmd *table, t_env **env, int fork)
{
	if (!ft_strcmp(cmd, "exit"))
	{
		ft_exit(table);
		return ;
	}
	if (!ft_strcmp(cmd, "env"))
	{
		ft_env(env, fork);
		return ;
	}
	if (!ft_strcmp(cmd, "pwd"))
	{
		ft_pwd(*env, fork);
		return ;
	}
}

void	unset_cd_echo_exp(char *cmd, t_cmd *table, t_env **env, int fork)
{
	if (!ft_strcmp(cmd, "unset"))
	{
		ft_unset(env, table, fork);
		return ;
	}
	if (!ft_strcmp(cmd, "cd"))
	{
		ft_cd(table, env, fork);
		return ;
	}
	if (!ft_strcmp(cmd, "echo"))
	{
		ft_echo(table, fork);
		return ;
	}
	if (!ft_strcmp(cmd, "export"))
	{
		ft_export(*env, table, fork);
		return ;
	}
}

void	which_builtin(char *cmd, t_cmd *table, t_env **env, int fork)
{
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd,
			"pwd"))
		exit_env_pwd(cmd, table, env, fork);
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"echo") || !ft_strcmp(cmd, "export"))
		unset_cd_echo_exp(cmd, table, env, fork);
}
