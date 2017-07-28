/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 17:21:29 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/22 18:19:54 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Surface		*convert_format(SDL_Surface *skybox)
{
	SDL_Surface *new;
	int			y;
	int			x;

	new = SDL_CreateRGBSurface(0, skybox->w, skybox->h, 32, 0, 0, 0, 0);
	y = -1;
	while (++y < skybox->h)
	{
		x = -1;
		while (++x < skybox->w)
		{
			((char*)(new->pixels))[(x + y * new->w) * 4] = \
							((char*)(skybox->pixels))[(x + y * new->w) * 3];
			((char*)(new->pixels))[(x + y * new->w) * 4 + 1] = \
							((char*)(skybox->pixels))[(x + y * new->w) * 3 + 1];
			((char*)(new->pixels))[(x + y * new->w) * 4 + 2] = \
							((char*)(skybox->pixels))[(x + y * new->w) * 3 + 2];
		}
	}
	return (new);
}

void			skybox_init(t_rt *r)
{
	cl_int		err;
	int			res;
	SDL_Surface *tmp;

	tmp = convert_format(r->sdl.skybox);
	SDL_FreeSurface(r->sdl.skybox);
	res = tmp->w * tmp->h;
	r->cl->k_data_skybox = clCreateBuffer(r->cl->context, CL_MEM_READ_ONLY,
									res * sizeof(cl_uint), NULL, &err);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_skybox,
						CL_TRUE, 0, res * sizeof(cl_uint),
						tmp->pixels, 0, NULL, NULL);
	SDL_FreeSurface(tmp);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 6, sizeof(cl_mem),
						(void *)&r->cl->k_data_skybox);
	check_ocl_error(err, r);
}
