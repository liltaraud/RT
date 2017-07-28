/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_table_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:45:23 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:04:42 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static cl_int		static_type(cl_int index, t_elm *objlst)
{
	cl_int				i;

	i = 0;
	while (objlst)
	{
		if (i == index)
			if (objlst->elm)
				return ((cl_int)((t_object *)objlst->elm)->type);
		i++;
		objlst = objlst->next;
	}
	return (0);
}

static cl_int		static_index(cl_int index, t_elm *objlst)
{
	cl_int				i;

	i = 0;
	while (objlst)
	{
		if (i == index)
			if (objlst->elm)
				return (((t_object *)objlst->elm)->buf_offset);
		i++;
		objlst = objlst->next;
	}
	return (0);
}

int					obj_table_init(t_scn *s)
{
	cl_int				i;
	int					nobj;
	int					sz;

	if (!s || !s->od || !(nobj = (cl_int)count_elm(s->obj)))
		return (0);
	s->nobj = nobj;
	s->odts = nobj * 2 + 1;
	sz = s->odts;
	free_ptr((void **)&s->ot);
	if (!(s->ot = (cl_int *)ft_memalloc(sizeof(cl_int) * s->odts)))
		return (0);
	i = 1;
	s->ot[0] = nobj;
	while (i < sz)
	{
		s->ot[i] = static_index(i / 2, s->obj);
		s->ot[i + 1] = static_type(i / 2, s->obj);
		i += 2;
	}
	return (1);
}
