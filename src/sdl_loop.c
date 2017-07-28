/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 17:33:46 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/24 16:55:29 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			camera_move(t_rt *r)
{
	if (r->sdl.keystate[Z_AXE] == 1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.dir, 0.2));
	if (r->sdl.keystate[Z_AXE] == -1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.dir, -0.2));
	if (r->sdl.keystate[X_AXE] == 1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.u, 0.2));
	if (r->sdl.keystate[X_AXE] == -1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.u, -0.2));
	if (r->sdl.keystate[Y_AXE] == 1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.v, 0.2));
	if (r->sdl.keystate[Y_AXE] == -1)
		r->cam.pos = vec_plus(r->cam.pos, vec_times_i(r->cam.v, -0.2));
	if (r->sdl.keystate[X_ROT] == 1 || r->sdl.keystate[X_ROT] == -1)
		rot_x(r, r->sdl.keystate[X_ROT]);
	if (r->sdl.keystate[Y_ROT] == 1 || r->sdl.keystate[Y_ROT] == -1)
		rot_y(r, r->sdl.keystate[Y_ROT]);
	if (r->sdl.keystate[Z_ROT] == 1 || r->sdl.keystate[Z_ROT] == -1)
		rot_z(r, r->sdl.keystate[Z_ROT]);
	cl_update_camera(r);
}

void			sdl_loop(t_rt *r)
{
	int				key;

	while (1)
	{
		while (SDL_PollEvent(&r->sdl.event))
			sdl_hook(r, r->sdl.event);
		key = -1;
		while (++key < 6)
			if (r->sdl.keystate[key])
				camera_move(r);
		if (r->sdl.keystate[ANIM])
			animate(r);
		cl_data_release(r);
		cl_objects_init(r);
		render(r);
		SDL_UpdateWindowSurface(r->sdl.p_win);
	}
}
