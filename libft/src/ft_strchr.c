/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:43:40 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/03 21:17:48 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	pc;
	size_t	i;

	i = 0;
	pc = c;
	if (!s || !c)
		return (NULL);
	while (s[i] != '\0' && s[i] != pc)
		i++;
	if (s[i] == pc)
		return ((char*)(s) + i);
	else if (pc == '\0')
		return ((char*)(s) + (ft_strlen(s) + 1));
	else
		return (NULL);
}
