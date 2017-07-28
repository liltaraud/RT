/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:32:29 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:16:39 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static int		static_next(char *c, uint *cnt, t_cone *con)
{
	int					cmp;

	if ((cmp = ft_strcmp("angle=", c)) <= -48 && cmp >= -57)
		if (++(*cnt) == 2 || !scn_parse_float(c + 6, &con->angle))
			return (0);
	return (1);
}

int				object_cone(char *c, t_object *o, t_elm **grb)
{
	t_cone				*con;
	uint				count;

	if (!(con = (t_cone *)malloc(sizeof(struct s_cone))) ||
		!push_elm(con, 'm', grb))
		return (0);
	count = 0;
	while (*(++c) && (*c != '<' || *(c + 1) != '/') && o)
		if (!static_next(c, &count, con))
			return (0);
	((cl_float *)&con->dir)[0] = o->mark.b[0];
	((cl_float *)&con->dir)[1] = o->mark.b[1];
	((cl_float *)&con->dir)[2] = o->mark.b[2];
	((cl_float *)&con->dir)[3] = 1;
	o->content = con;
	return (1);
}
