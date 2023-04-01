/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:09:22 by yismaail          #+#    #+#             */
/*   Updated: 2023/04/01 00:00:22 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	// if (s)
	// {
	// 	while (s[i])
	// 		i++;
	// 	return (i);
	// }
	// return (0);
	if (!s || !*s)
		return (0);
	while (s[i])
		i++;
	return (i);
}
