/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:48:53 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 17:19:50 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static char		*static_next_word(char *s)
{
	while (*s && !(*s == ' ' || *s == '\t'))
		s++;
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return (s);
}

static char		*next_tag(char *s, int *flg)
{
	int				cmp;

	if (*s == '<' && ft_isalpha(*(s + 1)))
		s++;
	while (((cmp = ft_strcmp("<", s)) < -122 || cmp > -97) &&
			(cmp = ft_strcmp("</scene", s)) != -62)
		if (!*(++s))
		{
			*flg = cmp;
			return (NULL);
		}
	*flg = cmp;
	return (*(s + 1) ? s + 1 : NULL);
}

static int		zero_scene(t_scn *scn, t_elm **grb)
{
	scn->info = NULL;
	scn->skybool = 1;
	scn->cam = NULL;
	scn->obj = NULL;
	scn->lgt = NULL;
	scn->grb = *grb;
	return (1);
}

t_scn			*new_scene(char *s, t_info *info, t_elm **grb)
{
	t_scn			*ret;
	int				flg;

	if (!(ret = (t_scn *)malloc(sizeof(struct s_scn))) || !zero_scene(ret, grb)
		|| !push_elm(ret, 'm', grb))
		return (NULL);
	ret->info = info;
	if (!(s = static_next_word(s)))
		return (NULL);
	if (ft_strcmp("name=", s) != -39 || !ft_strnccpy(ret->name, s + 6,
		NAME_BUF_LEN, '\'') || !(s = ft_strchr(s + 6, '\'')) ||
		*(s + 1) != '>')
		return (NULL);
	s += 2;
	while ((s = next_tag(s, &flg)) && flg != -62)
		if (!process_tag(s, ret, grb))
			return (NULL);
	ret->nobj = (size_t)count_elm(ret->obj);
	return (!s || ft_strcmp("/scene", s) != -62 ? NULL : ret);
}
