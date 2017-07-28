/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_paraboloid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:59:58 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:16:56 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				object_paraboloid(char *c, t_object *o, t_elm **grb)
{
	int					cmp;
	t_paraboloid		*par;
	uint				count;

	if (!(par = (t_paraboloid *)malloc(sizeof(struct s_paraboloid))) ||
		!push_elm(par, 'm', grb))
		return (0);
	count = 0;
	while (*(++c) && (*c != '<' || *(c + 1) != '/'))
	{
		if ((cmp = ft_strcmp("ray=", c)) <= -48 && cmp >= -57)
		{
			if (++count == 2 || !scn_parse_float(c + 4, &par->ray))
				return (0);
		}
	}
	((cl_float *)&par->dir)[0] = o->mark.b[0];
	((cl_float *)&par->dir)[1] = o->mark.b[1];
	((cl_float *)&par->dir)[2] = o->mark.b[2];
	((cl_float *)&par->dir)[3] = 1;
	return ((o->content = par) ? 1 : 0);
}
