/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:50:24 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 17:49:38 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	cmd_len(char **table)
{
	int	len;

	len = 0;
	while (table[len])
		len++;
	return (len);
}

void	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (cmd->cmd[1])
	{
		if (cmd_len(cmd->cmd) > 2)
		{
			while (cmd->cmd[1][i])
			{
				if (!ft_isdigit(cmd->cmd[1][i]))
					error_mess_exit(cmd->cmd[1]);
				i++;
			}
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			g_exec.g_exit_status = 1;
			return ;
		}
		else if (cmd_len(cmd->cmd) == 2)
		{
			g_exec.g_exit_status = my_ft_atoi(cmd->cmd[1]);
			exit(my_ft_atoi(cmd->cmd[1]));
		}
	}
	exit(g_exec.g_exit_status);
}
