/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:04:55 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/23 22:25:26 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					resize_win(t_rt *r, int change_cam)
{
	if (!r->sdl.screen)
		terminate(r, "Screen buffer error\n");
	SDL_FreeSurface(r->sdl.screen);
	if (change_cam && !r->sdl.fullscreen)
		SDL_SetWindowSize(r->sdl.p_win, r->size_x, r->size_y);
	r->sdl.screen = SDL_GetWindowSurface(r->sdl.p_win);
	r->size_x = r->sdl.screen->w;
	r->size_y = r->sdl.screen->h - MENU_BAR_H;
	if (r->sdl.screen->w == FULLSCREEN_MAC_SIZE_X && \
		r->sdl.screen->h == FULLSCREEN_MAC_SIZE_Y)
		r->sdl.fullscreen = ENABLED;
	else
		r->sdl.fullscreen = DISABLED;
	SDL_FreeSurface(r->gui.scene_info.scn);
	SDL_FreeSurface(r->gui.scene_info.cam);
	widgets_add(r);
	cl_update_camera(r);
	return (1);
}

void				mouse_camera(t_rt *r, int x, int y)
{
	x -= r->sdl.mousestate[1];
	y -= r->sdl.mousestate[2];
	if (x != 0)
		rot_y(r, x);
	if (y != 0)
		rot_x(r, y * -1);
	r->sdl.mousestate[1] += x;
	r->sdl.mousestate[2] += y;
	cl_update_camera(r);
}

static int			static_is_not_scncam(t_rt *r, SDL_Keycode key)
{
	int				type;

	if (key != SDLK_PAGEDOWN && key != SDLK_PAGEUP && key != SDLK_COMMA &&
		key != SDLK_PERIOD)
		return (1);
	if (key == SDLK_COMMA || key == SDLK_PERIOD)
		type = CAM;
	else
		type = SCN;
	if (r->sdl.keystate[CAM] != 0 || r->sdl.keystate[SCN] != 0)
		return (0);
	key == SDLK_COMMA ? r->sdl.keystate[CAM] = 1 : 0;
	key == SDLK_PERIOD ? r->sdl.keystate[CAM] = -1 : 0;
	key == SDLK_PAGEUP ? r->sdl.keystate[SCN] = 1 : 0;
	key == SDLK_PAGEDOWN ? r->sdl.keystate[SCN] = -1 : 0;
	if (!manage_cam_scn(r, key, type))
		terminate(r, "Switch env error\n");
	resize_win(r, 1);
	interface_draw(r);
	return (0);
}

void				sdl_hook(t_rt *r, SDL_Event event)
{
	int			redraw_gui;

	redraw_gui = 0;
	if (event.type == SDL_WINDOWEVENT && \
		event.window.event == SDL_WINDOWEVENT_CLOSE)
		terminate(r, NULL);
	if (event.type == SDL_WINDOWEVENT && \
		event.window.event == SDL_WINDOWEVENT_RESIZED)
		redraw_gui = resize_win(r, 0);
	if (event.type == SDL_KEYDOWN &&
		static_is_not_scncam(r, event.key.keysym.sym))
		key_press(event.key.keysym.sym, r);
	if (event.type == SDL_KEYUP)
		key_release(event.key.keysym.sym, r);
	if (event.type == SDL_MOUSEBUTTONDOWN)
		redraw_gui = mouse_hook_down(event.button.x, event.button.y, r);
	if (event.type == SDL_MOUSEBUTTONUP)
		mouse_hook_up(r);
	if (event.type == SDL_MOUSEMOTION && r->gui.filter.state)
		redraw_gui = interface_move(event.motion.x, r);
	if (event.type == SDL_MOUSEMOTION && r->sdl.mousestate[0] == 1)
		mouse_camera(r, event.motion.x, event.motion.y);
	if (redraw_gui)
		interface_draw(r);
}
