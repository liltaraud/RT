/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:09:37 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:35:52 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t		static_object_size(t_object *o)
{
	if (!o)
		return (0);
	if (o->type == OBJ_SPHERE)
		return (SZ_SPHERE);
	if (o->type == OBJ_CONE)
		return (SZ_CONE);
	if (o->type == OBJ_PLANE)
		return (SZ_PLANE);
	if (o->type == OBJ_CYLINDRE)
		return (SZ_CYLINDRE);
	if (o->type == OBJ_PARABOLOID)
		return (SZ_PARABOLOID);
	return (0);
}

static size_t		lstdat(t_scn *s)
{
	size_t			datsz;
	t_elm			*e;
	t_object		*o;

	e = s->obj;
	datsz = 0;
	while (e)
	{
		o = e->elm;
		datsz += static_object_size(o);
		e = e->next;
	}
	s->ods = datsz;
	return (datsz);
}

int					obj_init(t_scn *s)
{
	cl_int			offset;
	t_elm			*e;
	t_object		*o;
	cl_float		*ptr;

	if (!s || !s->obj || !(e = s->obj) ||
		!(s->od = (cl_float *)ft_memalloc(sizeof(cl_float) * lstdat(s))))
		return (0);
	ptr = s->od;
	offset = 0;
	e = s->obj;
	while (e)
	{
		o = e->elm;
		if (!(ptr += obj_dump(o, ptr, &offset)))
			return (0);
		e = e->next;
	}
	return (1);
}
