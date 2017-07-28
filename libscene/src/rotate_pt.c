/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_pt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:44:44 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/02 15:47:54 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static void			static_rot_next(float ax[3], float lv[3], float csn[2],
									float *lev)
{
	float				p[3];

	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	p[0] += (csn[0] + (1 - csn[0]) * ax[0] * ax[0]) * lv[0];
	p[0] += ((1 - csn[0]) * ax[0] * ax[1] - ax[2] * csn[1]) * lv[1];
	p[0] += ((1 - csn[0]) * ax[0] * ax[2] + ax[1] * csn[1]) * lv[2];
	p[1] += ((1 - csn[0]) * ax[0] * ax[1] + ax[2] * csn[1]) * lv[0];
	p[1] += (csn[0] + (1 - csn[0]) * ax[1] * ax[1]) * lv[1];
	p[1] += ((1 - csn[0]) * ax[1] * ax[2] - ax[0] * csn[1]) * lv[2];
	p[2] += ((1 - csn[0]) * ax[0] * ax[2] - ax[1] * csn[1]) * lv[0];
	p[2] += ((1 - csn[0]) * ax[1] * ax[2] + ax[0] * csn[1]) * lv[1];
	p[2] += (csn[0] + (1 - csn[0]) * ax[2] * ax[2]) * lv[2];
	lev[0] = p[0];
	lev[1] = p[1];
	lev[2] = p[2];
}

static void			static_rot(float axis[4], float a, float *lev)
{
	float				ax[3];
	float				lv[3];
	float				csn[2];

	csn[0] = (float)cos(a);
	csn[1] = (float)sin(a);
	ax[0] = axis[0];
	ax[1] = axis[1];
	ax[2] = axis[2];
	lv[0] = lev[0];
	lv[1] = lev[1];
	lv[2] = lev[2];
	static_rot_next(ax, lv, csn, lev);
}

void				rotate_pt(cl_float4 *ax, float angle, cl_float4 *pt)
{
	float			a;
	float			axis[4];

	if (!ax || !pt)
		return ;
	a = 3.1415926535 * angle / 180;
	axis[0] = ((float *)ax)[0];
	axis[1] = ((float *)ax)[1];
	axis[2] = ((float *)ax)[2];
	static_rot(axis, a, (float *)pt);
}
