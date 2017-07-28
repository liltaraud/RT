/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scn_parse_float4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 16:33:20 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/17 20:15:07 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static cl_float4	static_zero(void)
{
	cl_float4			ret;

	((float *)&ret)[0] = 0;
	((float *)&ret)[1] = 0;
	((float *)&ret)[2] = 0;
	((float *)&ret)[3] = 1;
	return (ret);
}

static int			static_error(char *c, int i[2], void **nulliferr)
{
	if (i[1] == 2 || (i[0] != 1 && *c == '-') ||
		(!ft_isdigit(*c) && (*c != '.' && *c == '-')))
	{
		*nulliferr = NULL;
		return (1);
	}
	return (0);
}

cl_float4			scn_parse_float4(char *c, void **nulliferr)
{
	cl_float4			ret;
	float				v[4];
	int					i[2];
	int					j;

	j = -1;
	v[3] = 1;
	ret = static_zero();
	while (++j < 3)
	{
		v[j] = (float)ft_atod(c);
		i[0] = 0;
		i[1] = 0;
		while (*(++c) && *c != ':' && *c != ' ' && *c != '\t' && *c != '\n')
		{
			i[0]++;
			i[1] += *c == '.' ? 1 : 0;
			if (static_error(c, i, nulliferr))
				return (ret);
		}
		if (!*c || (*(++c) == ':' && i[0] == 0 && !(nulliferr = NULL)))
			return (ret);
	}
	ret = *((cl_float4 *)&v);
	return (ret);
}
