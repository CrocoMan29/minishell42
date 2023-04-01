/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:51 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/01 01:28:03 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_args(int ac, char **av, t_env **dup_env, char **env)
{
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("noo we don't do that here", 2);
		exit(1);
	}
	parse_env(env, dup_env);
}

// void	minishell(char **env,t_env **dup_env)
// {
// 	int i;
	
// 	i = 0;
// 	while (env[i])
// 		i++;
// 	g_env = (char **)malloc((char *) * (i + 1));
// 	i = -1;
// 	while (env[i++])
// 		g_env[i] = env[i];
// 	g_env[i] = NULL;
// }

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_env	*dup_env;

	line = NULL;
	token = NULL;
	// (void)env;
	dup_env = NULL;
	check_args(ac, av, &dup_env, env);
	while (1)
	{
		
		
		line = readline("minishell>");
		if (!line)
			exit(1);
		 add_history(line);
		if (token_line(line, &token))
		{
			// printf("%s=", dup_env->key);
			// printf("%s\n", dup_env->value);
			// dup_env = dup_env->next;
			// if (!dup_env->next)
			// 	return (0);
			// printf("%s\n", dup_env->key);
			// printf("%s\n\n", dup_env->value);
			
			// dup_env->value=minishell(env, &dup_env);
			// int c = 8;
			// // if (!dup_env)
			// // 	return (0);
			// while (c-- > 0)
			// {
			// 	printf ("-->%s==", dup_env->key);
			// 	printf ("%s\n", dup_env->value);
			// 	dup_env = dup_env->next;
			// }
		}
	}
}
