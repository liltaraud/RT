/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 17:01:12 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/19 17:38:22 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strnstr2(size_t *i, size_t *j, size_t *len)
{
	*i = *i - *j;
	if (*j > 0)
		*len += *j - 1;
	else
		*len -= 1;
	*j = 0;
	*i += 1;
	return (0);
}

char		*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (len == 0)
		return (NULL);
	while (s1[i] != '\0' && len > 0)
	{
		while (s1[i] == s2[j] && s2[j] != '\0' && len > 0)
		{
			i++;
			j++;
			len--;
		}
		if (s2[j] == '\0')
			break ;
		ft_strnstr2(&i, &j, &len);
	}
	if (s2[j] == '\0')
		return ((char *)(s1) + (i - j));
	return (NULL);
}
