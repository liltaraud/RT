/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:33:40 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/11 19:13:51 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_float4	static_f4_vec(t_vec v)
{
	cl_float4		ret;

	((cl_float *)&ret)[0] = v.x;
	((cl_float *)&ret)[1] = v.y;
	((cl_float *)&ret)[2] = v.z;
	((cl_float *)&ret)[3] = 1;
	return (ret);
}

static t_vec		static_vec_f4(cl_float4 v)
{
	t_vec			ret;

	ret.x = ((cl_float *)&v)[0];
	ret.y = ((cl_float *)&v)[1];
	ret.z = ((cl_float *)&v)[2];
	return (ret);
}

void				rot_x(t_rt *r, int v)
{
	cl_float4	tmp[2];

	tmp[0] = static_f4_vec(r->cam.u);
	tmp[1] = static_f4_vec(r->cam.v);
	rotate_pt(&tmp[0], (float)v * -1.0, &tmp[1]);
	r->cam.v = static_vec_f4(tmp[1]);
	tmp[1] = static_f4_vec(r->cam.dir);
	rotate_pt(&tmp[0], (float)v * -1.0, &tmp[1]);
	r->cam.dir = static_vec_f4(tmp[1]);
}

void				rot_y(t_rt *r, int v)
{
	cl_float4	tmp[2];

	tmp[0] = static_f4_vec(r->cam.v);
	tmp[1] = static_f4_vec(r->cam.u);
	rotate_pt(&tmp[0], (float)v * 1.0, &tmp[1]);
	r->cam.u = static_vec_f4(tmp[1]);
	tmp[1] = static_f4_vec(r->cam.dir);
	rotate_pt(&tmp[0], (float)v * 1.0, &tmp[1]);
	r->cam.dir = static_vec_f4(tmp[1]);
}

void				rot_z(t_rt *r, int v)
{
	cl_float4	tmp[2];

	tmp[0] = static_f4_vec(r->cam.dir);
	tmp[1] = static_f4_vec(r->cam.u);
	rotate_pt(&tmp[0], (float)v * -1.0, &tmp[1]);
	r->cam.u = static_vec_f4(tmp[1]);
	tmp[1] = static_f4_vec(r->cam.v);
	rotate_pt(&tmp[0], (float)v * -1.0, &tmp[1]);
	r->cam.v = static_vec_f4(tmp[1]);
}
