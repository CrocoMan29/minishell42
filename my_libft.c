/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_libft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharit <meharit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:56:28 by meharit           #+#    #+#             */
/*   Updated: 2023/06/14 17:45:40 by meharit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*ft_my_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = NULL;
	if (s1 == 0 || s2 == 0)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_my_strjoin2(char *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = -1;
	ptr = NULL;
	if (s1 == 0 || s2 == 0)
		return (0);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[++j] != '\0')
	{
		ptr[i] = s2[j];
		i++;
	}
	free(s1);
	ptr[i] = '\0';
	return (ptr);
}

void	error_mess_exit(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_exec.g_exit_status = 255;
	exit(g_exec.g_exit_status);
}

int	my_ft_atoi(const char *str)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i + 1])
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > LLONG_MAX)
			error_mess_exit((char *)str);
		i++;
	}
	if ((str[i] && !ft_isdigit(str[i])))
		error_mess_exit((char *)str);
	return (((int)result * sign));
}

int	my_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (str[0] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
