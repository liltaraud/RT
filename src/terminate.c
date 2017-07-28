/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k3ungy <k3ungy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:36:14 by k3ungy            #+#    #+#             */
/*   Updated: 2017/05/23 15:42:37 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			static_free_lst(t_elm *e, int flg)
{
	t_elm			*fr;

	while (e)
	{
		fr = e;
		free_ptr((void **)&e->elm);
		e = e->next;
		if (flg)
			free_ptr((void **)&fr);
	}
}

static void			free_parser(t_rt *r)
{
	t_elm				*s;
	t_scn				*scn;
	t_elm				*garbage;

	s = r->scnstk;
	garbage = NULL;
	while (s)
	{
		if ((scn = s->elm))
		{
			if (!garbage)
				garbage = scn->grb;
			free_scene(scn);
		}
		s = s->next;
	}
	static_free_lst(garbage, 1);
}

static void			free_sdl_objects(t_rt *r)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		if (i < 2 && r->gui.bmp[i])
			SDL_FreeSurface(r->gui.bmp[i]);
		if (r->gui.texte[i])
			SDL_FreeSurface(r->gui.texte[i]);
	}
	if (r->gui.scene_info.scn)
		SDL_FreeSurface(r->gui.scene_info.scn);
	if (r->gui.scene_info.cam)
		SDL_FreeSurface(r->gui.scene_info.cam);
	if (r->sdl.screen)
		SDL_FreeSurface(r->sdl.screen);
	if (r->sdl.p_win)
		SDL_DestroyWindow(r->sdl.p_win);
	TTF_CloseFont(r->sdl.police);
}

void				terminate(t_rt *r, char *msg)
{
	free_sdl_objects(r);
	if (r->cl)
	{
		cl_data_release(r);
		cl_flush(r);
	}
	if (r->scnstk)
		free_parser(r);
	TTF_Quit();
	SDL_Quit();
	if (msg)
		ft_putendl(msg);
	exit(0);
}
