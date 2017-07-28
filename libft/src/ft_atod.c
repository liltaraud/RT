/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 16:04:39 by ttrossea          #+#    #+#             */
/*   Updated: 2017/04/22 15:38:10 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double			ft_atod(const char *str)
{
	long double			i[2];
	int					n;
	double				ac;
	double				bc;

	ac = 0;
	bc = 0;
	i[0] = 0;
	i[1] = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if ((n = (*str == '-' ? -1 : 1)) == -1 || *str == '+')
		str++;
	while (ft_isdigit(*str))
		ac = ac * 10 + (*str++ - '0');
	if (*str++ != '.')
		return (n * ac);
	while (ft_isdigit(*str))
	{
		i[0]++;
		bc = bc * 10 + (*str++ - '0');
	}
	while (i[0]--)
		i[1] = i[1] * 10;
	return (n * (ac + (bc / i[1])));
}
