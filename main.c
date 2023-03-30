/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:51 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/30 01:01:24 by yismaail         ###   ########.fr       */
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
	parse_env()
}

void	minishell(char **env,t_env **dup_env)
{
	int i;
	
	i = 0;
	while (env[i])
		i++;
	g_env = (char **)malloc((char *) * (i + 1));
	i = -1;
	while (env[i++])
		g_env[i] = env[i];
	g_env[i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_env	*dup_env;
	
	line = NULL;
	// (void)env;
	check_args(ac, av, &dup_env, env);
	while (1)
	{
		token = NULL;
		dup_env = NULL;
		line = readline("minishell>");
		if (!line)
			exit(1);
		if (token_line(line, &token))
		{
			dup_env->value=minishell(env, &dup_env);
			// int c = 6;
			// while (c > 0)
			// {
			// 	printf ("-->%s\n", token->content);
			// 	printf ("---%d\n----", token->type);
			// 	token = token->next;
			// }
		}
	}
}
