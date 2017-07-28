/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:41:34 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/17 20:02:35 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	pc;
	size_t			i;

	i = 0;
	pc = c;
	if (n <= 0)
		return (NULL);
	while (i < n)
	{
		if (*(unsigned char *)(s + i) == pc)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
