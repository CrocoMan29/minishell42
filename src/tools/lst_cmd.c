/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 08:47:36 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/29 01:44:42 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd  *ft_lstnew_cmd(void)
{
    t_cmd *new;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new)
        return (NULL);
	new->err = 0;
    new->next = NULL;
    return (new);
}

t_cmd  *ft_lstlast_cmd(t_cmd *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
    t_cmd *last;

	last = *lst;
    if (!(*lst))
    {
        *lst = new;
        return ;
    }
    while (last->next)
		last = last->next;
    last->next = new;
}

int	ft_strchr_2(const char *str, int c)
{
	char			*ptr;
	int				i;
	unsigned char	ch;

	i = 0;
	ptr = (char *)str;
	ch = c;
	if (!str)
		return (0);
	while (ptr[i])
	{
		if (ptr[i] == ch)
			return (i);
		i++;
	}
	if (ptr[i] == ch)
		return (i);
	return (0);
}

// void	ft_lstdelone_t(t_token *lst)
// {
// 	if (lst)
// 	{
// 		if (lst->content)
// 			free(lst->content);
// 		free(lst);
// 	}
// }

// void	ft_lstclear_t(t_token **lst)
// {
// 	t_token *tmp;
// 	t_token	*p;

// 	if (!lst)
// 		return ;
// 	p = *lst;
// 	while (p)
// 	{
// 		tmp = p->next;
// 		ft_lstdelone_t(p);
// 		p = tmp;
// 	}
// 	*lst = NULL;
// }