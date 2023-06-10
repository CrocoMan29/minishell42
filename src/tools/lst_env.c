/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:24:02 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/27 23:40:21 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*ft_lstnew_env(char *key, char *value, int val)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->valid = val;
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = new;
}

void	ft_remove(t_token *tmp, t_token **curr, t_token **token)
{
	t_token	*exp;

	if (!tmp)
	{
		*token = (*curr)->next;
		ft_lstdelone_t(*curr);
		(*curr) = NULL;
	}
	else
	{
		exp = (*curr)->next;
		ft_lstdelone_t(*curr);
		tmp->next = exp;
		*curr = exp;
	}
}

int	ft_putendl_fd_2(char *s, char *str, int fd)
{
	if (!s)
	{
		write (fd, "\n", 1);
		return (0);
	}
	if (str && *str == '/')
		str++;
	while (*s)
	{
		write (fd, s, 1);
		s++;
	}
	if (str)
	{
		write(fd, "`", 1);
		while (*str)
		{
			write (fd, str, 1);
			str++;
		}
		write(fd, "\'", 1);
	}
	write (fd, "\n", 1);
	exec.g_exit_status = 258;
	return (0);
}
