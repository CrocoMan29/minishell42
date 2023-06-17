/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:42:54 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 14:15:27 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_head(t_env **head_ptr)
{
	t_env	*second_node;

	if (*head_ptr == NULL || (*head_ptr)->next == NULL)
		return ;
	second_node = (*head_ptr)->next;
	(*head_ptr)->next = second_node->next;
	free((*head_ptr)->key);
	free((*head_ptr)->value);
	*head_ptr = second_node;
}

void	unset_var(t_env *env, int index, t_env **head)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = 0;
	if (index == 0)
		new_head(head);
	while (env)
	{
		if (i == index - 1)
		{
			new = (env->next)->next;
			tmp = env->next;
			free(tmp->key);
			free(tmp->value);
			env->next = new;
			break ;
		}
		i++;
		env = env->next;
	}
}

int	ident_valid(char *ident)
{
	int	i;

	i = 0;
	if (!ft_isalpha(ident[0]))
	{
		if (ident[0] == '\\' || ident[0] == '_')
			i++;
		else
			return (0);
	}
	while (ident[i])
	{
		if (!ft_isalpha(ident[i]) && !ft_isdigit(ident[i]) && ident[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	unset(t_env **dup_env, char *cmd, t_env *tmp)
{
	int	index;

	index = 0;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, cmd) == 0)
		{
			unset_var(*dup_env, index, dup_env);
			break ;
		}
		index++;
		tmp = tmp->next;
	}
	free(tmp);
}

void	ft_unset(t_env **dup_env, t_cmd *cmd, int fork)
{
	int		i;
	t_env	*tmp;

	i = 1;
	g_exec.g_exit_status = 0;
	if (cmd_len(cmd->cmd) > 1)
	{
		while (cmd->cmd[i])
		{
			tmp = *dup_env;
			if (ft_strcmp(cmd->cmd[i], "_"))
			{
				if (!ident_valid(cmd->cmd[i]))
					error_mess_uns(cmd->cmd[i]);
				unset(dup_env, cmd->cmd[i], tmp);
			}
			i++;
		}
	}
	if (fork)
		exit(g_exec.g_exit_status);
}
