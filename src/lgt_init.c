/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgt_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:35:14 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 15:25:38 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t		static_lgt_size(t_lgt *l)
{
	if (!l)
		return (0);
	if (l->type == LGT_SUN)
		return (SZ_SUN);
	if (l->type == LGT_SPT)
		return (SZ_SPT);
	return (0);
}

static size_t		static_lgt_dump(t_lgt *l, cl_float *p, cl_float *offset)
{
	size_t				count;

	if (!l || !p || !offset || (count = 0))
		return (0);
	l->buf_offset = *offset;
	p[0] = ((float *)&l->unit_color)[0];
	p[1] = ((float *)&l->unit_color)[1];
	p[2] = ((float *)&l->unit_color)[2];
	p[3] = l->intensity;
	p[4] = ((float *)&l->pos)[0];
	p[5] = ((float *)&l->pos)[1];
	p[6] = ((float *)&l->pos)[2];
	if (l->type == LGT_SPT)
	{
		p[7] = ((float *)&l->dir)[0];
		p[8] = ((float *)&l->dir)[1];
		p[9] = ((float *)&l->dir)[2];
		*offset += 3;
		count += 3;
	}
	*offset += SZ_SUN;
	count += SZ_SUN;
	return (count);
}

static size_t		count_size(t_scn *s)
{
	t_elm				*e;
	t_lgt				*l;
	size_t				datsz;

	datsz = 0;
	e = s->lgt;
	while (e)
	{
		l = (t_lgt *)e->elm;
		datsz += static_lgt_size(l);
		e = e->next;
	}
	s->lds = datsz;
	return (datsz);
}

int					lgt_init(t_scn *s)
{
	void				*lgt[2];
	cl_float			*ptr;
	cl_float			offset;

	if (!s || !s->lgt)
		return (0);
	if (!(s->ld = (cl_float *)ft_memalloc(sizeof(cl_float) * count_size(s))))
		return (0);
	lgt[0] = s->lgt;
	ptr = s->ld;
	offset = 0;
	while (lgt[0])
	{
		lgt[1] = (void *)((t_elm *)lgt[0])->elm;
		if (!(ptr += static_lgt_dump((t_lgt *)lgt[1], ptr, &offset)))
			return (0);
		lgt[0] = (void *)((t_elm *)lgt[0])->next;
	}
	return (lgt_table_init(s));
}
