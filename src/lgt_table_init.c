/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgt_table_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:08:12 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 15:16:06 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_int		static_type(cl_int index, t_elm *lgtlst)
{
	cl_int				i;

	i = 0;
	while (lgtlst)
	{
		if (i == index)
			if (lgtlst->elm)
				return (((t_lgt *)lgtlst->elm)->type);
		i++;
		lgtlst = lgtlst->next;
	}
	return (0);
}

static cl_int		static_index(cl_int index, t_elm *lgtlst)
{
	cl_int				i;

	i = 0;
	while (lgtlst)
	{
		if (i == index)
			if (lgtlst->elm)
				return (((t_lgt *)lgtlst->elm)->buf_offset);
		i++;
		lgtlst = lgtlst->next;
	}
	return (0);
}

int					lgt_table_init(t_scn *s)
{
	cl_int				i;
	int					nlgt;
	int					sz;

	if (!s || !s->ld)
		return (0);
	nlgt = (cl_int)count_elm(s->lgt);
	s->lts = nlgt * 2 + 1;
	sz = s->lts;
	if (!(s->lt = (cl_int *)ft_memalloc(sizeof(cl_int) * s->lts)))
		return (0);
	i = 1;
	s->lt[0] = nlgt;
	while (i < sz)
	{
		s->lt[i] = static_index(i / 2, s->lgt);
		s->lt[i + 1] = static_type(i / 2, s->lgt);
		i += 2;
	}
	return (1);
}
