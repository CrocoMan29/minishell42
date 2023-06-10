/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 07:24:03 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/23 13:14:14 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exp_here(int curr, int next)
{
	if (curr == '$' && next == '?')
		return (1);
	if (curr == '$' && !must_expand(next))
		return (1);
	return (0);
}

int	count(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '?')
		return (1);
	while (str[i] && !must_expand(str[i]))
		i++;
	return (i);
}

void	ft_free_2(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	free(str2);
	free(str3);
}

void	expand_var(t_env *env, char **content)
{
	t_help	help;

	help.str = NULL;
	help.str1 = NULL;
	help.join = NULL;
	help.last_str = NULL;
	help.i = 0;
	help.prev = *content;
	while (help.prev[help.i] && !exp_here(help.prev[help.i],
			help.prev[help.i + 1]))
		help.i++;
	if (!help.prev[help.i] || !help.prev[help.i + 1])
		return ;
	if (help.i)
		help.str = ft_substr(help.prev, 0, help.i);
	help.j = help.i + 1 + count(help.prev + help.i + 1);
	help.str1 = get_value_of_exp(env, ft_substr(help.prev,
				help.i + 1, help.j - help.i - 1));
	help.join = ft_strjoin(help.str, help.str1);
	if (ft_strlen(help.prev + help.j))
		help.last_str = ft_substr(help.prev,
				help.j, ft_strlen(help.prev + help.j));
	*content = ft_strjoin(help.join, help.last_str);
	ft_free_2(help.last_str, help.prev, help.str1);
	expand_var(env, content);
}
