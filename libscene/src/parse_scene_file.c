/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 13:38:43 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 17:31:35 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static t_info	*is_scene(char *p, t_elm **grb)
{
	int			cmp;
	double		ver;

	if (ft_strlen(p) < 12)
		return (NULL);
	if ((cmp = ft_strcmp("[RTscene]", p)) < -49 && cmp > -57)
		return (NULL);
	p += 9;
	ver = ft_atod(p);
	if (ver != 1.0)
		return (NULL);
	return (make_info(ver, p, grb));
}

static int		is_scene_tag(char *p)
{
	if (ft_strcmp("<scene", p) != -32)
		return (0);
	return (1);
}

static t_elm	*static_finish(t_elm *ret, char *dat)
{
	free_ptr((void **)&dat);
	return (ret);
}

t_elm			*parse_scene_file(char *filename)
{
	char			*dat[2];
	t_elm			*stk[2];
	t_info			*info;
	t_scn			*scn;

	if (ft_strcmp(".rt", filename + (ft_strlen(filename) - 3)) != 0)
		return (NULL);
	stk[1] = NULL;
	if (!(dat[0] = ft_read_file(filename)) ||
		!(dat[1] = dat[0]) ||
		!(info = is_scene(++dat[0], &stk[1])))
		return (NULL);
	stk[0] = NULL;
	while (*dat[0])
	{
		if (is_scene_tag(dat[0]))
		{
			if (!(scn = new_scene(dat[0], info, &stk[1])) ||
				!push_elm(scn, 'S', &stk[0]))
				return (NULL);
		}
		dat[0]++;
	}
	return (static_finish(stk[0], dat[1]));
}
