/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:51 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/17 05:40:24 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("noo we don't do that here", 2);
		exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	
	line = NULL;
	(void)env;
	check_args(ac, av);
	while (1)
	{
		token = NULL;
		line = readline("minishell>");
		if (!line)
			exit(1);
		if (token_line(line, &token))
			printf("%s\n", token->content);
	}
}