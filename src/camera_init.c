/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 22:23:21 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 15:04:24 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		camera_init_next(t_rt *r, t_cam *c)
{
	cl_float	half_w;
	cl_float	half_h;
	cl_float	w_coef;

	half_w = r->size_x / (cl_float)2.0;
	half_h = r->size_y / (cl_float)2.0;
	w_coef = half_h / (float)tan(0.65 * 0.5);
	r->cam.u.x = c->mark.a[0];
	r->cam.u.y = c->mark.a[1];
	r->cam.u.z = c->mark.a[2];
	r->cam.u = vec_normalize(r->cam.u);
	r->cam.v = vec_cross(r->cam.dir, r->cam.u);
	r->cam.v = vec_normalize(r->cam.v);
	r->cam.w = vec_times_i(r->cam.u, -half_w);
	r->cam.w = vec_plus(r->cam.w, vec_times_i(r->cam.v, half_h));
	r->cam.w = vec_plus(r->cam.w, vec_times_i(r->cam.dir, w_coef));
	return (1);
}

int				camera_init(t_rt *r, t_cam *c)
{
	if (!r || !c)
		return (0);
	r->size_x = c->dimx;
	r->size_y = c->dimy;
	r->cam.dir.x = ((float *)&c->dir)[0];
	r->cam.dir.y = ((float *)&c->dir)[1];
	r->cam.dir.z = ((float *)&c->dir)[2];
	r->cam.dir = vec_normalize(r->cam.dir);
	r->cam.pos.x = ((float *)&c->pos)[0];
	r->cam.pos.y = ((float *)&c->pos)[1];
	r->cam.pos.z = ((float *)&c->pos)[2];
	r->gws[0] = r->size_x * r->size_y;
	return (camera_init_next(r, c));
}
