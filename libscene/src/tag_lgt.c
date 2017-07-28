/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_lgt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 17:56:17 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 19:33:25 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static void			static_zero(t_lgt *l)
{
	((float *)&l->pos)[0] = 0;
	((float *)&l->pos)[1] = 0;
	((float *)&l->pos)[2] = 0;
	((float *)&l->pos)[3] = 1;
	((float *)&l->dir)[0] = 0;
	((float *)&l->dir)[1] = 0;
	((float *)&l->dir)[2] = 1;
	((float *)&l->dir)[3] = 1;
	l->type = 0;
	l->intensity = -1;
}

static int			static_verify(char *c, t_lgt *l, t_scn *s, t_elm **grb)
{
	if (!l)
		return (0);
	if (ft_strcmp("</lgt", c) == -62)
	{
		if (((float *)&l->unit_color)[0] >= 1.000001 ||
			((float *)&l->unit_color)[1] >= 1.000001 ||
			((float *)&l->unit_color)[2] >= 1.000001)
			return (0);
		if (!l->type)
			return (0);
		l->intensity = l->intensity < 0.0f ? 0 : l->intensity;
		return (!push_elm(l, 'L', &s->lgt) || !push_elm(l, 'm', grb) ? 0 : 1);
	}
	return (0);
}

static char			static_lgt_type(char *c)
{
	if (!ft_isdigit(*c) || (ft_isdigit(*c) && *(c + 1) != ' ' && *(c + 1)
		!= '\t' && *(c + 1) != '\n'))
		return (0);
	if (*c == '0')
		return (LGT_SUN);
	if (*c == '1')
		return (LGT_SPT);
	return (0);
}

static int			static_next(char *c, t_lgt *l, int cmp)
{
	if (((cmp = ft_strcmp("intensity=", c)) <= -48 && cmp >= -57))
		if (l->intensity != -1 || !scn_parse_float(c + 10, &l->intensity))
			return (0);
	return (1);
}

int					tag_lgt(char *c, t_scn *s, t_elm **grb)
{
	int			cmp;
	t_lgt		*l;

	if (ft_strcmp("name=", c) != -39 ||
		!(l = (t_lgt *)malloc(sizeof(struct s_lgt))) || !ft_strnccpy(l->name, c
		+ 6, NAME_BUF_LEN, '\'') || !(c = ft_strchr(c + 6, '\'')) || *(c + 1) !=
		'>' || !*(c = c + 2))
		return (0);
	static_zero(l);
	while (*(++c) && (*c != '<' || *(c + 1) != '/') && l)
	{
		if ((cmp = ft_strcmp("type=", c)) <= -48 && cmp >= -57 && *(c - 1) !=
			'_' && (l->type != 0 || (l->type = static_lgt_type(c + 5)) == 0))
			return (0);
		if (((cmp = ft_strcmp("pos=", c)) <= -48 && cmp >= -57) || cmp == -45)
			l->pos = scn_parse_float4(c + 4, (void **)&l);
		if (((cmp = ft_strcmp("color=", c)) <= -48 && cmp >= -57) || cmp == -45)
			l->unit_color = scn_parse_float4(c + 6, (void **)&l);
		if (!static_next(c, l, cmp))
			return (0);
	}
	return (static_verify(c, l, s, grb));
}
