/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylindre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:59:58 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:16:47 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				object_cylindre(char *c, t_object *o, t_elm **grb)
{
	int					cmp;
	t_cylindre			*cyl;
	uint				count;

	if (!(cyl = (t_cylindre *)malloc(sizeof(struct s_cylindre))) ||
		!push_elm(cyl, 'm', grb))
		return (0);
	count = 0;
	while (*(++c) && (*c != '<' || *(c + 1) != '/'))
	{
		if ((cmp = ft_strcmp("ray=", c)) <= -48 && cmp >= -57)
		{
			if (++count == 2 || !scn_parse_float(c + 4, &cyl->ray))
				return (0);
		}
	}
	((cl_float *)&cyl->dir)[0] = o->mark.b[0];
	((cl_float *)&cyl->dir)[1] = o->mark.b[1];
	((cl_float *)&cyl->dir)[2] = o->mark.b[2];
	((cl_float *)&cyl->dir)[3] = 1;
	return ((o->content = cyl) ? 1 : 0);
}
