/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:35:47 by ltaraud           #+#    #+#             */
/*   Updated: 2016/06/06 18:35:42 by k3ungy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		while (s1[i] == s2[j] && s2[j] != '\0')
		{
			i++;
			j++;
		}
		if (s2[j] == '\0')
			break ;
		i = i - j;
		j = 0;
		i++;
	}
	if (s2[j] == '\0')
		return ((char *)(s1) + (i - j));
	return (NULL);
}
