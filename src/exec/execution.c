/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 05:02:22 by meharit           #+#    #+#             */
/*   Updated: 2023/05/01 16:54:27 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	check_builin(char *cmd, t_cmd *table, t_env **env)
{
	if (ft_strcmp(cmd , "exit") == 0)
	{
		ft_exit(table);
		return ;
	}
	if (ft_strcmp(cmd , "env") == 0)
	{
		ft_env(env);
		return ;
	}
	if (ft_strcmp(cmd , "pwd") == 0)
	{
		ft_pwd();
		return ;
	}
	if (ft_strcmp(cmd , "unset") == 0)
	{
		ft_unset(env, table);
		return ;
	}
	if (ft_strcmp(cmd , "cd") == 0)
	{
		ft_cd(table, env);
		return ;
	}
	if (ft_strcmp(cmd , "echo") == 0)
	{
		ft_echo(table);
		return ;
	}
	if (ft_strcmp(cmd , "export") == 0)
	{
		ft_export(*env, table);
		return ;
	}
	printf("[%s] not builin\n", cmd);
}

void	execute(t_cmd *cmd, t_env **dup_env)
{
	int		i;

	i = 0;
	while (cmd)
	{
		check_builin(cmd->cmd[i], cmd, dup_env);
		cmd = cmd->next;
		// i++;
	}
}

