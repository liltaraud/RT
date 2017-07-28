/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:47:21 by ltaraud           #+#    #+#             */
/*   Updated: 2015/11/29 17:47:45 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	pc;

	pc = c;
	i = ft_strlen(s);
	while (i > 0 && s[i] != pc)
		i--;
	if (s[i] == pc)
		return ((char*)(s) + i);
	else if (pc == '\0')
		return (((char*)(s) + ft_strlen(s) + 1));
	else
		return (NULL);
}
