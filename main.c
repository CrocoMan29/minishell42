/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:51 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/11 04:50:05 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_minishell(char **env)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("minishell> ");
		get_token(line);
		
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1)
		return (0);
	ft_minishell(env);
}