/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnccpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:51:16 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/17 19:09:03 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnccpy(char *dst, const char *src, size_t n, char c)
{
	size_t		i;

	i = 0;
	if (!src || !dst)
		return (NULL);
	while (i < n - 1 && src[i] != '\0' && src[i] != c)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
