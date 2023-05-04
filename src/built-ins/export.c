/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:18:29 by meharit           #+#    #+#             */
/*   Updated: 2023/05/04 16:56:04 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	valid_ident(char *ident)
{
	int	i;

	i = 0;
	if (!ft_isalpha(ident[0]))
	{
		if (ident[0] == '\\' || ident[0] == '_')
		{
			printf("here\n");
			i++;
		}
		else
			return (0);
	}
	while (ident[i] != '=' && ident[i])
	{
		if (ident[i] != '+' && ident[i] != '=')
		{
			if (!ft_isalpha(ident[i]) && !ft_isdigit(ident[i]) && ident[i] != '_')
				return (0);
		}
		if (ident[i] == '+' && ident[i+1] != '=') //append
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
		ident++;         // start ident after '\'
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
		env->valid = 1;
	}
	else 
	{
		while (ft_strcmp(env->key, key))
			env = env->next;
		free(env->value);
		free(key);
		env->value = value;
		env->valid = 1;
	}
}

void	ft_export(t_env *dup_env, t_cmd *table)
{
	int	i;
	char	*key;
	char	*value;
	int		append; 

	i = 1;
	append = 0;
	if (cmd_len(table->cmd) == 1)
	{
		while (dup_env)
		{
			printf("declare -x ");
			printf("%s",dup_env->key);
			if (dup_env->valid)
				printf("=\"%s\"", dup_env->value);
			printf("\n");
			dup_env = dup_env->next;
		}
	}
	else
	{
		while (table->cmd[i])
		{
			if (valid_ident(table->cmd[i]))
			{
				key = get_key(table->cmd[i], &append);
				value = get_value(table->cmd[i]);
				if (!does_exist(key, dup_env))
				{
					if (env_valid(table->cmd[i]))
						ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 1));
					else
						ft_lstadd_back_env(&dup_env, ft_lstnew_env(key, value, 0));
				}
				else
					append_change(dup_env, &append, key, value);
			}
			else 
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(table->cmd[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				printf("%d\n",i);
			}
			i++;
		}
	}
}

//export "a    b   c" ?
