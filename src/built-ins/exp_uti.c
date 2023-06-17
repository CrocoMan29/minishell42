/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:33:18 by meharit           #+#    #+#             */
/*   Updated: 2023/06/13 17:23:04 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_mess_exp(char *cmd)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exec.g_exit_status = 1;
}

int	does_exist(char *key, t_env *dup_env)
{
	while (dup_env)
	{
		if (!ft_strcmp(key, dup_env->key))
			return (1);
		dup_env = dup_env->next;
	}
	return (0);
}

int	valid_ident(char *ident)
{
	int	i;

	i = 1;
	if (ident[0] != '_' && !ft_isalpha(ident[0]))
		return (0);
	while (ident[i] != '=' && ident[i])
	{
		if (ident[i] != '+' && ident[i] != '=')
		{
			if (ident[i] != '_' && !ft_isalpha(ident[i])
				&& !ft_isdigit(ident[i]))
				return (0);
		}
		if (ident[i] == '+' && ident[i + 1] != '=')
			return (0);
		i++;
	}
	return (1);
}

int	env_valid(char *ident)
{
	int	i;

	i = 0;
	while (ident[i])
	{
		if (ident[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	add_to(char *key, char *value, t_env *dup_env, char *ident)
{
	if (env_valid(ident))
		ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 1));
	else
		ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 0));
}
