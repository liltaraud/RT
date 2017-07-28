/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:59:55 by ltaraud           #+#    #+#             */
/*   Updated: 2016/05/31 18:45:57 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_atoi_2(const char *str, int i, size_t sign)
{
	size_t		res;

	res = 0;
	while (ft_isdigit(str[i]) == 1 && str[i] != '\0')
	{
		res = ((res * 10) + (str[i] - '0'));
		i++;
	}
	return ((res * sign));
}

int				ft_atoi(const char *str)
{
	size_t		i;
	size_t		sign;

	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] == '\t' || str[i] == '\v' || str[i] == '\r' ||
			str[i] == '\f' || str[i] == '\n' || str[i] == ' ')
		i++;
	if (str[i] == '-' && str[i + 1] != '+')
	{
		sign = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	return (ft_atoi_2(str, i, sign));
}
