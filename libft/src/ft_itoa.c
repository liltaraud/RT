/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 21:40:10 by ltaraud           #+#    #+#             */
/*   Updated: 2015/12/14 16:38:37 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numlen(int n)
{
	int				len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char		*ft_addnbr(char *res, int n, int i)
{
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	res[i] = (n % 10) + '0';
	if (n / 10 != 0)
		ft_addnbr(res, (n / 10), (i - 1));
	return (res);
}

char			*ft_itoa(int n)
{
	int		len;
	char	*res;

	len = ft_numlen(n);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == -2147483647 - 1)
		return (ft_strncpy(res, "-2147483648", 12));
	if (n == 2147483647)
		return (ft_strncpy(res, "2147483647", 12));
	res = ft_addnbr(res, n, (len - 1));
	res[len] = '\0';
	return (res);
}
