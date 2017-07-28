/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:10:26 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/22 18:25:53 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				checkbox_draw(t_checkbox tmp, t_rt *r)
{
	if (tmp.state == ENABLED)
		SDL_BlitSurface(\
			r->gui.bmp[ENABLED], NULL, r->sdl.screen, &tmp.box_pos_start);
	else
		SDL_BlitSurface(\
			r->gui.bmp[DISABLED], NULL, r->sdl.screen, &tmp.box_pos_start);
	SDL_BlitSurface(tmp.name, NULL, r->sdl.screen, &tmp.name_pos);
}

void				scrollbar_draw(t_scrollbar tmp, t_rt *r)
{
	unsigned int	*buf;
	unsigned int	color;
	int				y;
	int				x;

	buf = (unsigned int*)(r->sdl.screen->pixels);
	y = tmp.line_pos_start.y - 1;
	while (++y < tmp.line_pos_end.y)
	{
		x = tmp.line_pos_start.x - 1;
		while (++x < tmp.line_pos_end.x)
		{
			if (x >= tmp.value + tmp.line_pos_start.x && \
				x < tmp.value + tmp.line_pos_start.x + 25)
				color = tmp.color_cursor;
			else
				color = tmp.color_line;
			buf[y * r->size_x + x] = color;
		}
	}
	SDL_BlitSurface(tmp.name, NULL, r->sdl.screen, &tmp.name_pos);
}

void				scene_info_draw(t_scene_info tmp, t_rt *r)
{
	SDL_BlitSurface(tmp.scn, NULL, r->sdl.screen, &tmp.scn_pos);
	SDL_BlitSurface(tmp.cam, NULL, r->sdl.screen, &tmp.cam_pos);
}

void				gui_draw(t_rt *r)
{
	checkbox_draw(r->gui.skybox, r);
	scrollbar_draw(r->gui.filter, r);
	scene_info_draw(r->gui.scene_info, r);
}
