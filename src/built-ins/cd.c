/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:39 by meharit           #+#    #+#             */
/*   Updated: 2023/04/20 03:54:59 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_pwd(t_env **env, char *new_pwd)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp("PWD", tmp->key) == 0)
		{
			printf(RED"OLDPWD=%s\n"RESET, tmp->value);
			tmp->value = new_pwd;
			break ;
		}
		tmp = tmp->next;
	}
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	int		r_value;

	if (cmd_len(cmd->cmd) == 1)
	{
		get_pwd(env, "/Users/meharit/");      //change this
		chdir("/Users/meharit/");
		return ;
	}
	r_value = chdir(cmd->cmd[1]);
	if (r_value == 0) //path does exist
	{
		get_pwd(env, cmd->cmd[1]);
	}
	else if (r_value == -1) // path does not exist
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		perror(" ");
	}
	//update PWD and OLDPWD in env
}
