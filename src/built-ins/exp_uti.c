/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 19:33:18 by meharit           #+#    #+#             */
/*   Updated: 2023/04/30 18:07:10 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* t_exp  *ft_lstnew_exp(char *key, char *value)
{
    t_exp *new;

    new = (t_exp *)malloc(sizeof(t_exp));
    if (!new)
        return (NULL);
    new->key = key;
	new->value = value;
    new->next = NULL;
    return (new);
}

t_exp  *ft_lstlast_exp(t_exp *lst)
{
    if (!lst)
        return (NULL);
    while (lst->next)
        lst = lst->next;
    return (lst);
}

void    ft_lstadd_back_exp(t_exp **lst, t_exp *new)
{
    t_exp *last;
    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    last = ft_lstlast_exp(*lst);
    last->next = new;
}

void	fill_export(char *key, int index, t_env **dup_dup, t_exp **export)
{
	(void)export;
	
	t_env	*tmp;
	int		i;
	char	*value;
	// t_env	tmp;
	
	(void)index;
	(void) value;
	i = 0;
	tmp = *dup_dup;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
			// printf("the key =%s value = %s\n", key, tmp->value);
	tmp = tmp->next;
	}
	printf("------%s\n", (*dup_dup)->key);
	ft_lstadd_back_exp(export, ft_lstnew_exp(key, tmp->value));


	


	// unset_var(dup_dup, index, &dup_dup);
}

void    make_export_env(t_env *env, t_exp **export)
{
	int		index;
	t_env	*tmp;
	t_env	*add;
	t_exp	*print;
	int		move;
	int		i;
	int		y;

	move = 0;
	i = 0;
	add = env;
	while (env)
	{
		y = 0;
		index = 1;
		tmp = env->next;
		while (tmp)
		{
			if (ft_strcmp(env->key, tmp->key) > 0)
			{
				printf("index = %d tmp = %s env = %s \n", index, tmp->key, env->key);
				move = index;
				i = 0;
				while (i < index)
				{
					env = env->next; //fix
					tmp = env;
					i++;
				}
				y++;
				// break;
			}
			tmp = tmp->next;
			index++;
		}
		printf("-----------move =%s\n", env->key);
		fill_export(env->key, move, &add, export);

		//// THE EXP LINKED LIST
		print = *export;
		printf("THE EXP LINKED LIST\n");
		while (print)
		{
			printf("%s= %s\n", print->key, print->value);
			print = print->next;
		}

		env = env->next;

		if (!y)  //remove
		{
			printf("move env = %s\n", env->key);
			env = env->next;
		}

	}
} */
// put in export remove it from env check again from first
