/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 17:44:59 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/24 13:53:09 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				key_press(SDL_Keycode key, t_rt *r)
{
	if (key == SDLK_ESCAPE)
		terminate(r, 0);
	key == SDLK_w ? r->sdl.keystate[Z_AXE] = 1 : 0;
	key == SDLK_s ? r->sdl.keystate[Z_AXE] = -1 : 0;
	key == SDLK_d ? r->sdl.keystate[X_AXE] = 1 : 0;
	key == SDLK_a ? r->sdl.keystate[X_AXE] = -1 : 0;
	key == SDLK_SPACE ? r->sdl.keystate[Y_AXE] = 1 : 0;
	key == SDLK_LSHIFT ? r->sdl.keystate[Y_AXE] = -1 : 0;
	key == SDLK_UP ? r->sdl.keystate[X_ROT] = 1 : 0;
	key == SDLK_DOWN ? r->sdl.keystate[X_ROT] = -1 : 0;
	key == SDLK_RIGHT ? r->sdl.keystate[Y_ROT] = 1 : 0;
	key == SDLK_LEFT ? r->sdl.keystate[Y_ROT] = -1 : 0;
	key == SDLK_e ? r->sdl.keystate[Z_ROT] = 1 : 0;
	key == SDLK_q ? r->sdl.keystate[Z_ROT] = -1 : 0;
	if (!r->sdl.keystate[ANIM] && !r->sdl.is_key_pressed)
		key == SDLK_b ? r->sdl.keystate[ANIM] = 1 : 0;
	else if (!r->sdl.is_key_pressed)
		key == SDLK_b ? r->sdl.keystate[ANIM] = 0 : 0;
	r->sdl.is_key_pressed = 1;
	return (0);
}

int				key_release(SDL_Keycode key, t_rt *r)
{
	r->sdl.is_key_pressed = 0;
	key == SDLK_w ? r->sdl.keystate[Z_AXE] = 0 : 0;
	key == SDLK_s ? r->sdl.keystate[Z_AXE] = 0 : 0;
	key == SDLK_d ? r->sdl.keystate[X_AXE] = 0 : 0;
	key == SDLK_a ? r->sdl.keystate[X_AXE] = 0 : 0;
	key == SDLK_SPACE ? r->sdl.keystate[Y_AXE] = 0 : 0;
	key == SDLK_LSHIFT ? r->sdl.keystate[Y_AXE] = 0 : 0;
	key == SDLK_UP ? r->sdl.keystate[X_ROT] = 0 : 0;
	key == SDLK_DOWN ? r->sdl.keystate[X_ROT] = 0 : 0;
	key == SDLK_RIGHT ? r->sdl.keystate[Y_ROT] = 0 : 0;
	key == SDLK_LEFT ? r->sdl.keystate[Y_ROT] = 0 : 0;
	key == SDLK_e ? r->sdl.keystate[Z_ROT] = 0 : 0;
	key == SDLK_q ? r->sdl.keystate[Z_ROT] = 0 : 0;
	r->sdl.keystate[CAM] = 0;
	r->sdl.keystate[SCN] = 0;
	return (0);
}
