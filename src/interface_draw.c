/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 19:23:46 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/22 18:21:30 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				interface_draw(t_rt *r)
{
	SDL_FillRect(r->sdl.screen, NULL, \
		SDL_MapRGBA(r->sdl.screen->format, 211, 211, 211, 255));
	gui_draw(r);
}
