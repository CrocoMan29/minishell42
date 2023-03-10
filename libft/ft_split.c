/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaail <yismaail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:05:51 by yismaail          #+#    #+#             */
/*   Updated: 2022/11/04 01:30:30 by yismaail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wd_count(const char *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			k++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	if (k)
		return (k);
	return (1);
}

static void	ft_inc(const char *s, int *arr0, int *arr1, char c)
{
	while (s[*arr0] && s[*arr0] != c)
	{
		*arr0 += 1;
		*arr1 += 1;
	}
}

static char	**ft_free_tab(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**aldynamic;
	int		arr[4];

	if (!s)
		return (0);
	arr[0] = 0;
	arr[3] = 0;
	aldynamic = ft_calloc((wd_count(s, c) + 1), sizeof(char *));
	if (!aldynamic)
		return (NULL);
	while (s[arr[0]])
	{
		if (s[arr[0]] == c)
			arr[0]++;
		else
		{
			arr[2] = arr[0];
			arr[1] = 0;
			ft_inc(s, &arr[0], &arr[1], c);
			aldynamic[arr[3]] = ft_substr(s, arr[2], arr[1]);
			if (!(aldynamic[(arr[3])++]))
				return (ft_free_tab(aldynamic));
		}
	}
	return (aldynamic);
}

//int main()
//{
// 	printf("g\n");
// 	while (malloc(1024LL * 1024 * 1024))
// 		;
// 	printf("failed\n");
// 	while (malloc(100000))
// 		;
// 	printf("failed\n");
// 	while (malloc(1))
// 		;
// 	printf("hello\n");
// 	ft_split("ab", 'b');
//}