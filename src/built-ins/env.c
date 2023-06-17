/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:22:25 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 15:18:10 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_i(t_env **dup_env)
{
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("PWD"), getcwd(NULL, 0),
			1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("SHLVL"),
			ft_strdup("1"), 1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("_"), NULL, 1));
}

void	ft_env(t_env **dup_env, int fork)
{
	t_env	*tmp;

	tmp = *dup_env;
	while (tmp)
	{
		if (tmp->valid)
		{
			if (ft_strcmp(tmp->key, "_") == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup("/usr/bin/env");
			}
			printf("%s=", tmp->key);
			if (tmp->value)
				printf("%s", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}
	g_exec.g_exit_status = 0;
	if (fork)
		exit(g_exec.g_exit_status);
}

void	error_mess_uns(char *cmd)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exec.g_exit_status = 1;
}
