/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cam_scn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 21:37:43 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 16:44:27 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			manage_cam_scn(t_rt *r, SDL_Keycode key, int type)
{
	int			state;

	if (key == SDLK_PAGEDOWN || key == SDLK_COMMA)
		state = -1;
	else
		state = 1;
	if (!switch_env(r, type, state))
		return (0);
	return (1);
}
