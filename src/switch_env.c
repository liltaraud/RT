/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/13 20:14:27 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:04:36 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		*static_before_last(t_elm *stk)
{
	t_elm			*prev;

	if (!(prev = stk))
		return (NULL);
	while (stk->next)
	{
		prev = stk;
		stk = stk->next;
	}
	return (prev->elm);
}

static void		*static_last(t_elm *stk)
{
	while (stk->next)
		stk = stk->next;
	return (stk->elm);
}

static void		*static_find_elm(t_elm *beg, void *search, int event)
{
	t_elm			*e;

	e = beg;
	if (!event && beg)
		return (beg->elm);
	while (e)
	{
		if (event == 1)
			if (e->elm == search)
			{
				if (!(e->next))
					return (beg->elm);
				return (e->next->elm);
			}
		if (event == -1)
		{
			if (search == beg->elm)
				return (static_last(beg));
			if ((e->next && e->next->elm == search) || !e->next)
				return (e->next ? e->elm : static_before_last(beg));
		}
		e = e->next;
	}
	return (NULL);
}

int				switch_env(t_rt *r, int key, int event)
{
	if (key == SCN)
	{
		if (!(r->scn = (t_scn *)static_find_elm(r->scnstk,
						(void *)r->scn, event)))
			return (0);
		dump_var(r, r->scn);
		camera_init(r, r->curcam);
		if (event != 0)
			cl_objects_init(r);
	}
	if (key == CAM)
		if (!(r->curcam = (t_cam *)static_find_elm(r->scn->cam,
					(void *)r->curcam, event)) || !camera_init(r, r->curcam))
			return (0);
	return (1);
}
