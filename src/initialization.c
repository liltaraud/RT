/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 19:05:28 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 15:50:18 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		static_dump_values(t_scn *s)
{
	s->od = NULL;
	s->ot = NULL;
	s->ld = NULL;
	s->lt = NULL;
	s->skybool = 1;
	return (1);
}

int				initialization(t_rt *r, char *scenepath)
{
	t_elm		*e;
	t_scn		*scn;

	if (!(r->scnstk = parse_scene_file(scenepath)))
	{
		ft_putstr("Parsing error.\n");
		return (0);
	}
	e = r->scnstk;
	r->win_title = scenepath;
	while (e)
	{
		if (!(scn = e->elm) || !static_dump_values(scn))
			return (0);
		camera_init(r, (t_cam *)scn->cam->elm);
		if (!obj_init(scn) || !lgt_init(scn) || !obj_table_init(scn))
			return (0);
		e = e->next;
	}
	return (r->scnstk ? switch_env(r, SCN, 0) : 0);
}
