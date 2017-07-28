/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 15:04:36 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/23 18:27:12 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			draw_fps(t_rt *r)
{
	int				delta;
	float			newtime;
	char			*tmp;
	SDL_Surface		*texte;
	SDL_Rect		pos;

	tmp = NULL;
	pos.x = 5;
	pos.y = MENU_BAR_H + 5;
	newtime = SDL_GetTicks();
	delta = (newtime - r->oldtime);
	delta = (delta == 0) ? delta + 0.0001f : delta;
	r->oldtime = newtime;
	tmp = ft_itoa(1000.0 / delta);
	if (tmp)
	{
		texte = TTF_RenderText_Solid(r->sdl.police, tmp, r->sdl.color);
		if (texte)
		{
			SDL_BlitSurface(texte, NULL, r->sdl.screen, &pos);
			SDL_FreeSurface(texte);
		}
		free(tmp);
	}
}

void			render(t_rt *r)
{
	cl_int		err;

	err = clEnqueueNDRangeKernel(r->cl->cmd_queue, r->cl->k_lighting, 1,
								NULL, r->gws, r->lws, 0, NULL, NULL);
	check_ocl_error(err, r);
	clFinish(r->cl->cmd_queue);
	err = clEnqueueReadBuffer(r->cl->cmd_queue, r->cl->k_data_image, CL_TRUE,
						0, r->size_x * r->size_y * sizeof(cl_uint),
						r->sdl.screen->pixels + r->size_x * MENU_BAR_H * \
						r->sdl.screen->format->BytesPerPixel,
						0, NULL, NULL);
	check_ocl_error(err, r);
	clFinish(r->cl->cmd_queue);
	draw_fps(r);
}
