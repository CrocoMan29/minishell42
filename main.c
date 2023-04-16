/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:19:51 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/16 17:22:38 by yismaail         ###   ########.fr       */
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

void	remove_spaces(t_token **token, t_token *tok)
{
	t_token *tmp;
	
	tmp = NULL;
	while (tok)
	{
		if (tok->type == SPACE)
		{
			ft_remove(tmp, &tok, token);
		}
		else
		{
			tmp = tok;
			tok = tok->next;
		}
	}
}

void	ft_minishell(t_env **env, t_token **token, t_cmd **cmd)
{
	(void) cmd;

	t_token *tmp;

	tmp = *token;
	handler_expand(token, *env, *token);
	remove_spaces(token, *token);
	if (check_syntax(*token))
	{
		//parse_cmd(token, cmd);
		printf("lhamdolilah\n");
	}
	else
		ft_lstclear_t(token);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_token	*token;
	t_env	*dup_env;
	t_cmd	*cmd;

	line = NULL;
	token = NULL;
	cmd = NULL;
	dup_env = NULL;
	check_args(ac, av, &dup_env, env);
	while (1)
	{
		line = readline("minishell>");
		if (!line)
		{
			printf("exit\n"); //////
			exit(1);
		}
		add_history(line);
		if (token_line(line, &token))
		{	
			ft_minishell(&dup_env, &token, &cmd);


			// ft_exit();
			// ft_env(dup_env);




			// printf ("%s", token->content);
			// printf("yassir");
			// while (token)
			// {
			// 	printf("--|%d|--", token->type);
			// 	token = token->next;
			// }
			// printf("\n");
			// if (ft_strncmp(line, "env", 3) == 0)
			// {
			// 	while (dup_env)
			// 	{
			// 		printf("%s=", dup_env->key);
			// 		printf("%s\n", dup_env->value);
			// 		dup_env = dup_env->next;
			// 	}
			// }
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
