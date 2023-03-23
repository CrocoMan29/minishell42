/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback_m.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 05:16:07 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/23 14:31:31 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token  *ft_lstnew_m(char *content)
{
    t_token *new;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->content = content;
	new->type = type_token(content);
    new->next = NULL;
    return (new);
}

t_token  *ft_lstlast_m(t_token *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    ft_lstadd_back_m(t_token **lst, t_token *new)
{
    t_token *last;
    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last = ft_lstlast_m(*lst);
    last->next = new;
}