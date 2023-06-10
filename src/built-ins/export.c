/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:18:29 by meharit           #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_ident(char *ident)
{
	int	i;

	i = 1;
	if (!ft_isalpha(ident[0]))
	{
		if (ident[0] != '\\')
			return (0);
	}
	while (ident[i] != '=' && ident[i])
	{
		if (ident[i] != '+' && ident[i] != '=')
		{
			if (!ft_isalpha(ident[i]) && !ft_isdigit(ident[i]))
				return (0);
		}
		if (ident[i] == '+' && ident[i+1] != '=')
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

char	*get_key(char *ident, int *append)
{
	int	i;

	i = 0;
	if (ident[0] == '\\')
		ident++;         						// start ident after '\'
	while (ident[i] && ident[i] != '=' && ident[i] != '+')
		i++;
	if (ident[i] == '+')
		(*append) = 1;
	return (ft_substr(ident, 0, i));
}

char	*get_value(char *ident)
{
	int i;

	i = 0;
	while (ident[i] && ident[i] != '=')
		i++;
	if (!ident[i])
		return (ft_strdup(""));
	return (ft_substr(ident, i+1, ft_strlen(ident))); //skip =
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

void	append_change(t_env *env, int *append, char *key, char *value)
{
	if (*append)
	{
		while (ft_strcmp(env->key, key))
			env = env->next;
		env->value = ft_strjoin(env->value, value);
		free(value);
		free(key);
	}
	else 
	{
		while (ft_strcmp(env->key, key))
			env = env->next;
		free (key);
		free(env->value);
		env->value = value;
		env->valid = 1;
	}
}

void	export(t_env *dup_env, t_cmd *table) //??
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
				printf("%s",dup_env->key);
				if (dup_env->value)
					printf("=\"%s\"\n", dup_env->value);
			}
			dup_env = dup_env->next;
		}
		exec.g_exit_status = 0;
	}	
}

void	error_mess_exp(char *cmd)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	exec.g_exit_status = 1;
}

void	add_to(char *key, char *value, t_env *dup_env, char *ident)
{

	if (env_valid(ident))
		ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 1));
	else
		ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 0));
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
		exit (exec.g_exit_status);
}
