/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widgets_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:10:26 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/23 14:50:52 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_checkbox			add_checkbox(int x, int y, int state, SDL_Surface *name)
{
	t_checkbox		new;

	new.name = name;
	new.state = state;
	new.box_pos_start.x = x;
	new.box_pos_start.y = y;
	new.box_pos_end.x = x + 15;
	new.box_pos_end.y = y + 15;
	new.name_pos.x = new.box_pos_start.x + 20;
	new.name_pos.y = new.box_pos_start.y - 5;
	return (new);
}

t_scrollbar			add_scrollbar(int x, int y, int value, SDL_Surface *name)
{
	t_scrollbar		new;

	new.name = name;
	new.value = value;
	new.state = DISABLED;
	new.color_line = 255;
	new.color_line = (new.color_line << 8) + 200;
	new.color_line = (new.color_line << 8) + 200;
	new.color_line = (new.color_line << 8) + 200;
	new.color_cursor = 255;
	new.color_cursor = (new.color_cursor << 8) + 100;
	new.color_cursor = (new.color_cursor << 8) + 100;
	new.color_cursor = (new.color_cursor << 8) + 100;
	new.line_pos_start.x = x;
	new.line_pos_start.y = y;
	new.line_pos_end.x = x + 125;
	new.line_pos_end.y = y + 25;
	new.name_pos.x = new.line_pos_end.x + 5;
	new.name_pos.y = new.line_pos_end.y - 25;
	return (new);
}

t_scene_info		add_scene_info(int x, int y, t_rt *r)
{
	t_scene_info	new;

	new.scn_pos.x = x;
	new.scn_pos.y = y;
	new.cam_pos.x = x;
	new.cam_pos.y = y + 25;
	new.scn = TTF_RenderText_Solid(r->sdl.police, \
		r->scn->name, r->sdl.color);
	new.cam = TTF_RenderText_Solid(r->sdl.police, \
		r->curcam->name, r->sdl.color);
	return (new);
}

void				widgets_add(t_rt *r)
{
	r->gui.skybox = \
		add_checkbox(10, 45, r->gui.skybox.state, r->gui.texte[SKYBOX]);
	r->gui.filter = \
		add_scrollbar(150, 10, r->gui.filter.value, \
								r->gui.texte[r->filter + 1]);
	r->gui.scene_info = \
		add_scene_info(150, 40, r);
}
