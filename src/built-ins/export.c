/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:18:29 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 15:55:38 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *ident, int *append)
{
	int	i;

	i = 0;
	if (ident[0] == '\\')
		ident++;
	while (ident[i] && ident[i] != '=' && ident[i] != '+')
		i++;
	if (ident[i] == '=')
		(*append) = 2;
	else if (ident[i] == '+')
		(*append) = 1;
	return (ft_substr(ident, 0, i));
}

char	*get_value(char *ident)
{
	int	i;

	i = 0;
	while (ident[i] && ident[i] != '=')
		i++;
	if (!ident[i])
		return (ft_strdup(""));
	return (ft_substr(ident, i + 1, ft_strlen(ident)));
}

void	append_change(t_env *env, int *append, char *key, char *value)
{
	if (*append == 2 || value[0])
	{
		if (*append == 1)
		{
			while (ft_strcmp(env->key, key))
				env = env->next;
			env->value = ft_my_strjoin2(env->value, value);
			free(value);
			free(key);
		}
		else
		{
			while (ft_strcmp(env->key, key))
				env = env->next;
			free(key);
			free(env->value);
			env->value = value;
			env->valid = 1;
		}
	}
}

void	export(t_env *dup_env, t_cmd *table)
{
	if (cmd_len(table->cmd) == 1)
	{
		if (!dup_env)
			env_i(&dup_env);
		while (dup_env)
		{
			if (dup_env->value)
			{
				printf("declare -x ");
				printf("%s", dup_env->key);
				if (ft_strcmp(dup_env->value, ""))
					printf("=\"%s\"", dup_env->value);
				printf("\n");
			}
			dup_env = dup_env->next;
		}
		g_exec.g_exit_status = 0;
	}
}

void	ft_export(t_env *dup_env, t_cmd *table, int fork)
{
	int		i;
	char	*key;
	char	*value;
	int		append;

	i = 1;
	append = 0;
	export(dup_env, table);
	while (table->cmd[i])
	{
		if (valid_ident(table->cmd[i]))
		{
			key = get_key(table->cmd[i], &append);
			value = get_value(table->cmd[i]);
			if (!does_exist(key, dup_env))
				add_to(key, value, dup_env, table->cmd[i]);
			else
				append_change(dup_env, &append, key, value);
		}
		else
			error_mess_exp(table->cmd[i]);
		i++;
	}
	if (fork)
		exit(g_exec.g_exit_status);
}
