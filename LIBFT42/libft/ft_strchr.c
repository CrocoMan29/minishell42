/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 11:22:11 by yismaail          #+#    #+#             */
/*   Updated: 2022/10/25 23:45:00 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	symbole;

	str = (char *)s;
	symbole = (char)c;
	while (*str && !(*str == symbole))
		str++;
	if (*str == symbole)
		return (str);
	return (0);
}
