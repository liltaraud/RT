/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:30:38 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:16:30 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				object_sphere(char *c, t_object *o, t_elm **grb)
{
	int					cmp;
	t_sphere			*sph;
	uint				count[2];

	if (!(sph = (t_sphere *)malloc(sizeof(struct s_sphere))) ||
		!push_elm(sph, 'm', grb))
		return (0);
	count[0] = 0;
	count[1] = 0;
	while (*(++c) && (*c != '<' || *(c + 1) != '/'))
	{
		if ((cmp = ft_strcmp("ray=", c)) <= -48 && cmp >= -57)
		{
			if (++count[0] == 2 || !scn_parse_float(c + 4, &sph->ray))
				return (0);
		}
	}
	o->content = sph;
	return (1);
}
