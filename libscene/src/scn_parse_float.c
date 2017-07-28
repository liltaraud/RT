/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_parse_float.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 21:18:55 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 23:56:03 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int			scn_parse_float(char *c, float *val)
{
	uint			dot;

	if (!val)
		return (0);
	dot = 0;
	*val = ft_atod(c);
	while (*c && (ft_isdigit(*c) || *c == '.'))
	{
		if (*c == '.')
			if (++dot == 2)
				return (0);
		if (!*(c++))
			return (0);
	}
	if (!*c || (*c != ' ' && *c != '\t' && *c != '\n'))
		return (0);
	return (1);
}
