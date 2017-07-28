/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 12:31:43 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:17:09 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int			object_plane(t_object *o, t_elm **grb)
{
	t_plane				*pln;

	if (!o || !(pln = (t_plane *)malloc(sizeof(struct s_plane))) ||
		!push_elm(pln, 'm', grb))
		return (0);
	((cl_float *)&pln->dir)[0] = o->mark.b[0];
	((cl_float *)&pln->dir)[1] = o->mark.b[1];
	((cl_float *)&pln->dir)[2] = o->mark.b[2];
	((cl_float *)&pln->dir)[3] = 1;
	o->content = pln;
	return (1);
}
