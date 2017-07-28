/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:55:04 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/07 15:32:25 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*pc1;
	unsigned char	putin;

	putin = c;
	pc1 = b;
	i = 0;
	while (len > 0)
	{
		pc1[i] = putin;
		i++;
		len--;
	}
	return (b);
}
