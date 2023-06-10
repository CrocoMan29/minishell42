/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 20:50:24 by meharit           #+#    #+#             */
/*   Updated: 2023/06/09 16:13:18 by meharit          ###   ########.fr       */
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

int	my_ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if ((!str[i] && i == 1) || (str[i] && !ft_isdigit(str[i])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd((char *)str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exec.g_exit_status = 255;
		exit(exec.g_exit_status);
	}
	return (((int)result * sign));
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
	ft_putstr_fd("exit\n", 2);
	if (cmd->cmd[1])
	{
		printf("cmd_len = %d\n", cmd_len(cmd->cmd));
		if (cmd_len(cmd->cmd) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exec.g_exit_status = 1;
			return ;
		}
		else if (cmd_len(cmd->cmd) == 2)
		{
			printf("here\n");
			exec.g_exit_status = my_ft_atoi(cmd->cmd[1]);
			exit (my_ft_atoi(cmd->cmd[1]));
		}
	}
	exit (0);
}
