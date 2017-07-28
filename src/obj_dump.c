/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_dump.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 16:09:37 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:23:37 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t		static_next_bis_bis(t_object *o, cl_float *p,
						cl_int *offset, size_t ret)
{
	void				*tp;

	tp = o->content;
	if (o->type == OBJ_PARABOLOID)
	{
		p[10] = ((float *)&((t_paraboloid *)tp)->dir)[0];
		p[11] = ((float *)&((t_paraboloid *)tp)->dir)[1];
		p[12] = ((float *)&((t_paraboloid *)tp)->dir)[2];
		p[13] = ((t_paraboloid *)tp)->ray;
		p += SZ_PARABOLOID;
		*offset += SZ_PARABOLOID;
		ret += SZ_PARABOLOID;
	}
	return (ret);
}

static size_t		static_next_bis(t_object *o, cl_float *p, cl_int *offset,
						size_t ret)
{
	void				*tp;

	tp = o->content;
	if (o->type == OBJ_PLANE)
	{
		p[10] = ((float *)&((t_plane *)tp)->dir)[0];
		p[11] = ((float *)&((t_plane *)tp)->dir)[1];
		p[12] = ((float *)&((t_plane *)tp)->dir)[2];
		p += SZ_PLANE;
		*offset += SZ_PLANE;
		ret += SZ_PLANE;
	}
	if (o->type == OBJ_CYLINDRE)
	{
		p[10] = ((float *)&((t_cylindre *)tp)->dir)[0];
		p[11] = ((float *)&((t_cylindre *)tp)->dir)[1];
		p[12] = ((float *)&((t_cylindre *)tp)->dir)[2];
		p[13] = ((t_cylindre *)tp)->ray;
		p += SZ_CYLINDRE;
		*offset += SZ_CYLINDRE;
		ret += SZ_CYLINDRE;
	}
	return (static_next_bis_bis(o, p, offset, ret));
}

static size_t		static_next(t_object *o, cl_float *p, cl_int *offset)
{
	void				*tp;
	size_t				ret;

	ret = 0;
	if (o->type == OBJ_SPHERE)
	{
		p[10] = ((t_sphere *)o->content)->ray;
		p += SZ_SPHERE;
		*offset += SZ_SPHERE;
		ret += SZ_SPHERE;
	}
	tp = o->content;
	if (o->type == OBJ_CONE)
	{
		p[10] = ((float *)&((t_cone *)tp)->dir)[0];
		p[11] = ((float *)&((t_cone *)tp)->dir)[1];
		p[12] = ((float *)&((t_cone *)tp)->dir)[2];
		p[13] = ((t_cone *)tp)->angle;
		p += SZ_CONE;
		*offset += SZ_CONE;
		ret += SZ_CONE;
	}
	return (static_next_bis(o, p, offset, ret));
}

size_t				obj_dump(t_object *o, cl_float *p, cl_int *offset)
{
	t_mtl				*m;

	if (!o || !p || !o->content)
		return (0);
	o->buf_offset = *offset;
	m = &o->mtl;
	p[0] = ((cl_float *)&m->kd)[0];
	p[1] = ((cl_float *)&m->kd)[1];
	p[2] = ((cl_float *)&m->kd)[2];
	p[3] = m->ns;
	p[4] = m->ke;
	p[5] = 0.5;
	p[6] = m->ni;
	p[7] = ((float *)&o->pos)[0];
	p[8] = ((float *)&o->pos)[1];
	p[9] = ((float *)&o->pos)[2];
	return (static_next(o, p, offset));
}
