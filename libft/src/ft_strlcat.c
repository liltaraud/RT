/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:46:41 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/18 05:23:38 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		g;

	i = 0;
	g = ft_strlen(dst);
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	while ((g + i) < (size - 1) && src[i])
	{
		dst[g + i] = src[i];
		i++;
	}
	dst[g + i] = '\0';
	return (g + ft_strlen(src));
}
