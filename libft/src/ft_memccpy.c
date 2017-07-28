/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 10:09:48 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/07 22:35:18 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		pc;
	size_t				i;
	unsigned char		*dstt;

	dstt = dst;
	pc = c;
	i = 0;
	while ((*((unsigned char*)(src) + i) != pc) &&
			(*((unsigned char*)(src) + i) != '\0') && (n > 0))
	{
		*((unsigned char*)(dstt) + i) = *((unsigned char*)(src) + i);
		i++;
		n--;
	}
	if (n == 0 && *(unsigned char*)(src) + i != pc)
		return (NULL);
	else
	{
		*((unsigned char*)(dstt) + i) = *((unsigned char*)(src) + i);
		return ((void *)(dstt) + (i + 1));
	}
}
