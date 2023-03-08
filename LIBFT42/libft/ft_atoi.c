/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 19:30:20 by yismaail          #+#    #+#             */
/*   Updated: 2022/11/04 01:33:36 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_max(int nbr, int signe)
{
	unsigned long long	nb;

	nb = nbr;
	if (nb >= 9223372036854775807 && signe == -1)
		return (0);
	if (nb >= 9223372036854775807)
		return (-1);
	return (nb);
}

int	ft_atoi(const char *str)
{
	unsigned long long	i;
	int					signe;
	unsigned long long	nbr;

	i = 0;
	signe = 1;
	nbr = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		nbr = nbr * 10 + (str[i++] - 48);
	}
	check_max(nbr, signe);
	return (nbr * signe);
}
