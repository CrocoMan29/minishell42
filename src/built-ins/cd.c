/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:39 by meharit           #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_my_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = NULL;
	if (s1 == 0 || s2 == 0)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_pwd(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("PWD", env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_home(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

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
		}
		tmp = tmp->next;
	}
}

void	upd_pwd(t_env *env, char *pwd)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
			env->value = pwd;
		env = env->next;
	}
}

void	home(t_env **env)
{
	chdir(get_home(*env));
	if (get_home(*env))
	{
		upd_old_pwd(*env);
		upd_pwd(*env, get_home(*env));
	}
	else  		  //HOME unset
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		exec.g_exit_status = 1;
	}
}

void	ft_cd(t_cmd *cmd, t_env **env, int fork)
{
	int		r_value;
	char	*pwd;

	if (cmd_len(cmd->cmd) == 1)
	{
		home(env);
		exec.g_exit_status = 0;
		return ;
	}
	r_value = chdir(cmd->cmd[1]);
	if (r_value == 0) //path does exist
	{
		pwd = getcwd(NULL, 0);
		upd_old_pwd(*env);
		upd_pwd(*env, pwd);
		exec.g_exit_status = 0;
	}
	else if (r_value == -1) // path does not exist
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		perror(" ");
		exec.g_exit_status = 1;
	}
	if (fork)
		exit (exec.g_exit_status);
}