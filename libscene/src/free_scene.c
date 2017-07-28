/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 19:36:18 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 17:19:39 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static void		static_free_lst(t_elm *e, int flg)
{
	t_elm			*tmp;

	while (e)
	{
		tmp = e;
		e = e->next;
		if (flg)
			free_ptr((void **)&tmp->elm);
		free(tmp);
	}
}

void			free_scene(t_scn *s)
{
	if (!s)
		return ;
	static_free_lst(s->obj, 0);
	static_free_lst(s->cam, 0);
	static_free_lst(s->lgt, 0);
	free_ptr((void **)&s->od);
	free_ptr((void **)&s->ot);
	free_ptr((void **)&s->ld);
	free_ptr((void **)&s->lt);
}
