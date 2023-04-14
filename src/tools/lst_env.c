/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:24:02 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/14 05:12:07 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env  *ft_lstnew_env(char *key, char *value)
{
    t_env *new;

    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
	new->value = value;
    new->next = NULL;
    return (new);
}

t_env  *ft_lstlast_env(t_env *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    ft_lstadd_back_env(t_env **lst, t_env *new)
{
    t_env *last;
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
	if (!tmp)
	{
		*token = (*curr)->next;
		ft_lstdelone_t(*curr);
		(*curr) = NULL;
	}
	else
	{
		*token = (*curr)->next;
		ft_lstdelone_t(*curr);
		tmp->next = *token;
		*curr = tmp;
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
	// g_global_data.exit_status = 258;
	return (0);
}
// void	ft_lstclear(t_token **lst)
// {
// 	t_token	*ptr;
// 	t_token	*tmp;

// 	if (!lst)
// 		return ;
// 	ptr = *lst;
// 	while (ptr)
// 	{
// 		tmp = ptr->next;
// 		ft_lstdelone(ptr);
// 		ptr = tmp;
// 	}
// 	*lst = NULL;
// }

// void	ft_lstdelone(t_token *lst)
// {
// 	if (lst)
// 	{
// 		if (lst->content)
// 			free(lst->content);
// 		free(lst);
// 	}
// }
