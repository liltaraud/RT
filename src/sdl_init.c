/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:52:50 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/23 15:43:18 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			check_textures(int imax, SDL_Surface *tmp[imax], t_rt *r)
{
	int			i;

	i = -1;
	while (++i < imax)
		if (!tmp[i])
			terminate(r, "Load BMP error\n");
}

void			loadtexture(t_rt *r)
{
	r->sdl.skybox = SDL_LoadBMP("skybox/Skybox.bmp");
	if (!r->sdl.skybox)
		terminate(r, "Load BMP error\n");
	r->gui.bmp[0] = SDL_LoadBMP("gui/checkbox_no.bmp");
	r->gui.bmp[1] = SDL_LoadBMP("gui/checkbox_yes.bmp");
	check_textures(2, r->gui.bmp, r);
}

void			sdl_init(t_rt *r)
{
	r->sdl.p_win = NULL;
	r->sdl.p_win = SDL_CreateWindow(r->win_title, SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, r->size_x, r->size_y + MENU_BAR_H, \
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!r->sdl.p_win)
		terminate(r, "SDL window error\n");
	SDL_SetWindowMinimumSize(r->sdl.p_win, MIN_WINX, MIN_WINY);
	r->sdl.screen = SDL_GetWindowSurface(r->sdl.p_win);
	if (TTF_Init() < 0)
		terminate(r, "TTF init error\n");
	r->sdl.police = TTF_OpenFont("police.ttf", 16);
	if (!r->sdl.police)
		terminate(r, "TTF Open Font error\n");
	loadtexture(r);
	r->sdl.fullscreen = DISABLED;
}
