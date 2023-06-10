/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:22:25 by meharit           #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_i(t_env **dup_env)   // export when no env 
{
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("PWD"), getcwd(NULL, 0), 1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"), 1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("OLDPWD"), NULL, 1));
	ft_lstadd_back_env(dup_env, ft_lstnew_env(ft_strdup("_"), NULL, 1));
}

void	ft_env(t_env **dup_env, int fork)
{
	t_env *tmp;

	if (!(*dup_env))  // cd ~
	{
		env_i(dup_env);
		//add shell level
	}
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
				
			if (tmp->value)
				printf("%s=%s\n", tmp->key,tmp->value);
		}
			
		tmp = tmp->next;
	}
	exec.g_exit_status = 0;
	if (fork)
		exit (exec.g_exit_status);
}
