/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:17:54 by yismaail          #+#    #+#             */
/*   Updated: 2022/10/25 23:46:05 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cast;

	ptr = (char *)s + ft_strlen(s);
	cast = (char)c;
	while (ptr >= s)
	{
		if (*ptr == cast)
			return (ptr);
		ptr--;
	}
	return (NULL);
}
