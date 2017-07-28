/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k3ungy <k3ungy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:15:16 by k3ungy            #+#    #+#             */
/*   Updated: 2017/05/22 18:13:00 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				set_mouse_state(t_rt *r, int x, int y)
{
	r->sdl.mousestate[0] = 1;
	r->sdl.mousestate[1] = x;
	r->sdl.mousestate[2] = y;
	return (1);
}

int				is_inside(int x, int y, SDL_Rect start, SDL_Rect end)
{
	if (x >= start.x && x < end.x && y >= start.y && y < end.y)
		return (1);
	return (0);
}

int				mouse_hook_down(int x, int y, t_rt *r)
{
	if (y >= MENU_BAR_H && set_mouse_state(r, x, y))
		return (0);
	else if (is_inside(x, y, r->gui.skybox.box_pos_start, \
							r->gui.skybox.box_pos_end))
	{
		r->gui.skybox.state = r->gui.skybox.state == 1 ? 0 : 1;
		r->enable_skybox = r->gui.skybox.state;
	}
	else if (is_inside(x, y, r->gui.filter.line_pos_start, \
							r->gui.filter.line_pos_end))
	{
		r->gui.filter.state = r->gui.filter.state == 1 ? 0 : 1;
		interface_move(x, r);
	}
	else
		return (0);
	return (1);
}

int				mouse_hook_up(t_rt *r)
{
	r->sdl.mousestate[0] = 0;
	r->gui.filter.state = DISABLED;
	return (0);
}
