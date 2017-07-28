/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 21:32:35 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/23 21:53:43 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		move_sphere(int id, float *obj_data)
{
	obj_data[id + 8] = cos(SDL_GetTicks() * 0.001);
}

void			animate(t_rt *r)
{
	int			i;

	i = 0;
	while (i * 2 + 1 < r->obj_data_table_size)
	{
		if (r->obj_data_table[i * 2] == 1)
			move_sphere(r->obj_data_table[i * 2 + 1], r->obj_data);
		i++;
	}
}
