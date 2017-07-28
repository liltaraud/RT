/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 18:34:18 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/11 17:46:06 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	size_t			i;
	void			*ret;

	if (!(ret = ft_memalloc(new_size > size ? new_size : size)))
		return (NULL);
	if (!ft_memcpy(ret, ptr, size))
		return (NULL);
	if (new_size <= size)
		return (ret);
	i = size - 1;
	while (++i < new_size)
		((char *)ret)[i] = (char)0;
	return (ret);
}
