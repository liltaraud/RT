/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:22:24 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:21:34 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static int		static_obj_type(char *c)
{
	if (ft_strcmp("sphere", c) == -39)
		return (OBJ_SPHERE);
	if (ft_strcmp("cone", c) == -39)
		return (OBJ_CONE);
	if (ft_strcmp("plane", c) == -39)
		return (OBJ_PLANE);
	if (ft_strcmp("cylindre", c) == -39)
		return (OBJ_CYLINDRE);
	if (ft_strcmp("paraboloid", c) == -39)
		return (OBJ_PARABOLOID);
	return (0);
}

static void		static_rot_object(t_object *o)
{
	if (!o)
		return ;
	if (((cl_float *)&o->rot)[0] != 0)
	{
		rotate_pt((cl_float4 *)&o->mark.a, ((cl_float *)&o->rot)[0],
				(cl_float4 *)&o->mark.b);
		rotate_pt((cl_float4 *)&o->mark.a, ((cl_float *)&o->rot)[0],
				(cl_float4 *)&o->mark.c);
	}
	if (((cl_float *)&o->rot)[1] != 0)
	{
		rotate_pt((cl_float4 *)&o->mark.b, ((cl_float *)&o->rot)[1],
				(cl_float4 *)&o->mark.a);
		rotate_pt((cl_float4 *)&o->mark.b, ((cl_float *)&o->rot)[1],
				(cl_float4 *)&o->mark.c);
	}
	if (((cl_float *)&o->rot)[2] != 0)
	{
		rotate_pt((cl_float4 *)&o->mark.c, ((cl_float *)&o->rot)[2],
				(cl_float4 *)&o->mark.a);
		rotate_pt((cl_float4 *)&o->mark.c, ((cl_float *)&o->rot)[2],
				(cl_float4 *)&o->mark.b);
	}
}

static int		static_verify(char *c[2], char type, t_object *o, t_scn *s)
{
	static uint		id = 0;
	int				ret;

	if (!o || !c[0] || !c[1] || !(*c[0]) || !(*c[1]))
		return (0);
	if (ft_strcmp("</obj", c[1]) == -62)
	{
		if (!verify_mtl(&o->mtl))
			return (0);
		o->mark = new_mark();
		static_rot_object(o);
		if (type == OBJ_SPHERE)
			ret = object_sphere(c[0], o, &s->grb);
		if (type == OBJ_CONE)
			ret = object_cone(c[0], o, &s->grb);
		if (type == OBJ_PLANE)
			ret = object_plane(o, &s->grb);
		if (type == OBJ_CYLINDRE)
			ret = object_cylindre(c[0], o, &s->grb);
		if (type == OBJ_PARABOLOID)
			ret = object_paraboloid(c[0], o, &s->grb);
		o->id = id++;
		return (ret != 0 ? push_elm(o, 'O', &s->obj) : 0);
	}
	return (0);
}

static int		static_next(char *c, t_object *o)
{
	int				cmp;

	if (((cmp = ft_strcmp("rot=", c)) <= -48 && cmp >= -57) || cmp == -45)
		o->rot = scn_parse_float4(c + 4, (void **)&o);
	if ((cmp = ft_strcmp("color=", c)) <= -48 && cmp >= -57 &&
		is_pagin(*(c - 1)))
		o->mtl.kd = scn_parse_float4(c + 6, (void **)&o);
	if ((cmp = ft_strcmp("rough=", c)) <= -48 && cmp >= -57 &&
		is_pagin(*(c - 1)))
		return (scn_parse_float(c + 6, (void *)&o->mtl.ns));
	if ((cmp = ft_strcmp("refl=", c)) <= -48 && cmp >= -57 &&
		is_pagin(*(c - 1)))
		return (scn_parse_float(c + 5, (void *)&o->mtl.ke));
	if ((cmp = ft_strcmp("mtl_type=", c)) <= -48 && cmp >= -57 &&
			is_pagin(*(c - 1)))
		return (scn_parse_float(c + 9, &o->mtl.ni));
	return (1);
}

int				tag_obj(char *c, t_scn *s, t_elm **grb)
{
	int				cmp;
	char			*obj[2];
	t_object		*o;

	if (ft_strcmp("name=", c) != -39 ||
		!(o = (t_object *)ft_memalloc(sizeof(struct s_object))) ||
		!ft_strnccpy(o->name, c + 6, NAME_BUF_LEN, '\'') || !push_elm(o, 'm',
		grb) || !(c = ft_strchr(c + 6, '\'')) || *(c + 1) != '>' ||
		!*(c = c + 2) || !init_mtl(&o->mtl))
		return (0);
	o->content = NULL;
	obj[0] = c;
	while (*(++c) && (*c != '<' || *(c + 1) != '/') && o)
	{
		if (ft_strcmp("type=", c) == -39)
			if (o->type != 0 || !(o->type = static_obj_type(c + 6)))
				return (0);
		if (((cmp = ft_strcmp("pos=", c)) <= -48 && cmp >= -57) ||
			cmp == -45)
			o->pos = scn_parse_float4(c + 4, (void **)&o);
		if (!static_next(c, o))
			return (0);
	}
	obj[1] = c;
	return (o ? static_verify(obj, o->type, o, s) : 0);
}
