/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:39 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 16:08:17 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	upd_old_pwd(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp("OLDPWD", tmp->key) == 0)
		{
			free(tmp->value);
			tmp->value = get_pwd(env);
			return ;
		}
		tmp = tmp->next;
	}
}

void	upd_pwd(t_env *env, char *pwd)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
		{
			free(env->value);
			env->value = ft_strdup(pwd);
			return ;
		}	
		env = env->next;
	}
}

void	home(t_env **env)
{
	char	*home;

	home = get_home(*env);
	if (home && chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(home, 2);
		perror(" ");
		g_exec.g_exit_status = 1;
	}
	if (home)
	{
		upd_old_pwd(*env);
		upd_pwd(*env, home);
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_exec.g_exit_status = 1;
	}
	free (home);
}

void	upd_env_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	upd_old_pwd(env);
	upd_pwd(env, pwd);
	free (pwd);
	g_exec.g_exit_status = 0;
}

void	ft_cd(t_cmd *cmd, t_env **env, int fork)
{
	int	r_value;

	if (cmd_len(cmd->cmd) == 1 || !cmd->cmd[1][0])
	{
		home(env);
		if (fork)
			exit(g_exec.g_exit_status);
		return ;
	}
	r_value = chdir(cmd->cmd[1]);
	if (r_value == 0)
		upd_env_pwd(*env);
	else if (r_value == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		perror(" ");
		g_exec.g_exit_status = 1;
	}
	if (fork)
		exit(g_exec.g_exit_status);
}
