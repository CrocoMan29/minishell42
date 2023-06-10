/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:26:44 by meharit           #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_if_option(char *str, int *opt)
{
	int i;

	i = 1;
	if (!str)
		return ;
	if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] != 'n')
				return ;
			i++;
		}
		*opt = 1;
	}
}

void	ft_echo(t_cmd *cmd, int fork)
{
	int	opt;
	int	i;

	opt = 0;
	i = 1;
	check_if_option(cmd->cmd[1], &opt);
	if (opt)
		i++;
	while (cmd->cmd[i])
	{
		printf("%s",cmd->cmd[i]);
		if (i < cmd_len(cmd->cmd) - 1)
			printf(" ");
		i++;
	}
	if (!opt)
		printf("\n");
	exec.g_exit_status = 0;
	if (fork)
		exit (exec.g_exit_status);
}
