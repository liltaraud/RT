/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 18:47:54 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/24 13:47:24 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				police_init(t_rt *r)
{
	r->gui.texte[SKYBOX] = TTF_RenderText_Solid(r->sdl.police, \
		"Skybox", r->sdl.color);
	r->gui.texte[NO_FILTER] = TTF_RenderText_Solid(r->sdl.police, \
		"No_filter", r->sdl.color);
	r->gui.texte[SEPIA] = TTF_RenderText_Solid(r->sdl.police, \
		"Sepia", r->sdl.color);
	r->gui.texte[GRAYSCALE] = TTF_RenderText_Solid(r->sdl.police, \
		"Grayscale", r->sdl.color);
	r->gui.texte[CELSHADE] = TTF_RenderText_Solid(r->sdl.police, \
		"Celshade", r->sdl.color);
}

void				gui_init(t_rt *r)
{
	r->sdl.color.r = 255;
	r->sdl.color.g = 255;
	r->sdl.color.b = 255;
	r->sdl.color.a = 255;
	r->sdl.image_pos.x = 0;
	r->sdl.image_pos.y = MENU_BAR_H;
	r->gui.skybox.state = r->enable_skybox;
	r->gui.filter.state = DISABLED;
	r->sdl.keystate[0] = 0;
	r->sdl.keystate[1] = 0;
	r->sdl.keystate[2] = 0;
	r->sdl.keystate[3] = 0;
	r->sdl.keystate[4] = 0;
	r->sdl.keystate[5] = 0;
	r->sdl.keystate[6] = 0;
	r->sdl.keystate[7] = 0;
	r->sdl.keystate[8] = 0;
	r->sdl.is_key_pressed = 0;
	police_init(r);
	widgets_add(r);
}
