/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:32:11 by yismaail          #+#    #+#             */
/*   Updated: 2023/03/09 22:37:02 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last;
    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last = ft_lstlast(*lst);
    last->next = new;
}
