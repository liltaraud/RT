/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get_ws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 14:28:02 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/22 12:53:24 by fdeclerc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cl_get_ws(t_rt *r)
{
	size_t		size[20];

	r->gws[0] = r->size_x * r->size_y;
	clGetDeviceInfo(r->cl->device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
								sizeof(size_t) * 20, &size, NULL);
	r->lws[0] = size[0];
	if (r->lws[0] == 0)
		terminate(r, "Error With Work Sizes\n");
	while (r->lws[0] > r->gws[0] || r->gws[0] % r->lws[0] != 0)
		r->lws[0] /= 2;
}
