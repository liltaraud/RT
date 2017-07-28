/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 19:50:44 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/15 20:01:36 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*p;

	p = (void *)malloc(size);
	if (p != NULL)
		ft_memset((void *)p, 0, size);
	return ((void *)(p));
}
