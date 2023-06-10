/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 11:38:29 by yismaail          #+#    #+#             */
/*   Updated: 2023/05/18 07:45:13 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstadd_back_redi(t_redi **lst, t_redi *new)
{
	t_redi	*last;

	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (last->next)
		last = last->next;
	last->next = new;
}

t_redi	*ft_lstnew_redi(char *out, int type)
{
	t_redi	*ptr;

	ptr = malloc(sizeof(t_redi));
	if (!ptr)
		return (NULL);
	ptr->file = out;
	ptr->must_exp = 0;
	ptr->type = type;
	ptr->next = NULL;
	return (ptr);
}

t_redi	*ft_lstlast_redi(t_redi *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear_2(t_redi **lst)
{
	t_redi	*ptr;
	t_redi	*tmp;

	if (!lst)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->file);
		free(ptr);
		ptr = tmp;
	}
	*lst = NULL;
}

int	is_all_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] != ' ' || str[i] != '\n' || str[i] != '\t'))
			return (0);
		i++;
	}
	return (1);
}
