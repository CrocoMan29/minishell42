/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 00:24:02 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/31 00:38:40 by yismaail         ###   ########.fr       */
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