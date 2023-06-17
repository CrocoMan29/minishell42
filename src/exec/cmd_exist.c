/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:03:35 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 00:48:43 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**find_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (ft_split(env->value, ':'));
		env = env->next;
	}
	return (NULL);
}

void	directory_error(char *dir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": is a directory\n", 2);
	g_exec.g_exit_status = 126;
	exit(g_exec.g_exit_status);
}

char	*directory_executable(t_cmd *table)
{
	DIR	*ptr_dir;

	ptr_dir = opendir(table->cmd[0]);
	if (ptr_dir)
		directory_error(table->cmd[0]);
	if (table->cmd[0][0] == '/' || (table->cmd[0][0] == '.'
			&& table->cmd[0][1] == '/'))
	{
		if (access(table->cmd[0], F_OK) == 0)
			return (table->cmd[0]);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(table->cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_exec.g_exit_status = 127;
			exit(g_exec.g_exit_status);
		}
	}
	return (NULL);
}

char	*cmd_path(char **path, char *cmd)
{
	char	*test;
	int		i;

	i = 0;
	while (path[i])
	{
		test = ft_strjoin(path[i], cmd);
		if (access(test, F_OK) == 0)
			return (test);
		i++;
	}
	if (my_strchr(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd + 1, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exec.g_exit_status = 127;
		exit(g_exec.g_exit_status);
	}
	return (NULL);
}

char	*cmd_exist(t_cmd *table, t_env *env)
{
	char	**path;
	char	*cmd;
	char	*retrn;

	if (!table->cmd)
		return (NULL);
	retrn = directory_executable(table);
	if (retrn)
		return (retrn);
	if (table->cmd[0][0])
	{
		cmd = ft_my_strjoin("/", table->cmd[0]);
		path = find_path(env);
		if (path)
			return (cmd_path(path, cmd));
	}
	return (NULL);
}
