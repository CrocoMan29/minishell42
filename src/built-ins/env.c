/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:22:25 by meharit           #+#    #+#             */
/*   Updated: 2023/04/15 21:33:05 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *dup_env)
{
	t_env *tmp;

	tmp = dup_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

