/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:41:39 by meharit           #+#    #+#             */
/*   Updated: 2023/05/04 17:50:32 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

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
	printf("homeless T-T\n");
	return (NULL);
}

void	ft_cd(t_cmd *cmd, t_env **env)
{
	char	*old_pwd;
	int		r_value;

	if (cmd_len(cmd->cmd) == 1)
	{
		old_pwd = ft_my_strjoin("OLD_PWD=", get_pwd(*env));
		printf("%s\n", old_pwd);
		// cmd->cmd[0] = ft_strdup("export");
		cmd->cmd[1] = old_pwd;
		printf("good\n");
		ft_export(*env, cmd);
		chdir(get_home(*env));
		return ;
	}
	r_value = chdir(cmd->cmd[1]);
	if (r_value == 0) //path does exist
	{
		// get_pwd(env, cmd->cmd[1]);
	}
	else if (r_value == -1) // path does not exist
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		perror(" ");
	}
	//update PWD and OLDPWD in env
}
