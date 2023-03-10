/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:49:02 by yismaail          #+#    #+#             */
/*   Updated: 2022/11/02 12:50:30 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	symbole;

	symbole = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == symbole)
			return (str);
		str++;
	}
	return (NULL);
}
