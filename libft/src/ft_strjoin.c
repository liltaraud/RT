/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:43:48 by ltaraud           #+#    #+#             */
/*   Updated: 2016/04/20 10:51:48 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res != NULL)
	{
		while (s1 && s1[i] != '\0')
		{
			res[i] = s1[i];
			i++;
		}
		while (s2 && s2[j] != '\0')
		{
			res[i] = s2[j];
			j++;
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
