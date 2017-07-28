/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 12:05:08 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/21 17:19:48 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static char			*next_author(char *p)
{
	while (ft_strcmp("<author", p) != -32)
		if (!*(p++))
			return (NULL);
	return (p + 8);
}

static int			fill_date(char *p, t_auth *a)
{
	int			d;
	int			i;

	d = -1;
	while (++d < 2)
	{
		if (d == 0)
			a->date.day = ft_atoi(p);
		else
			a->date.month = ft_atoi(p);
		if (!ft_isdigit(*p))
			return (0);
		i = 0;
		while (ft_isdigit(*p++))
			i++;
		if (!*p || *(p - 1) != '/' || i > 2)
			return (0);
	}
	if (ft_strlen(p) < 5 || !ft_isdigit(*p) || !ft_isdigit(*(p + 1)) ||
		!ft_isdigit(*(p + 2)) || !ft_isdigit(*(p + 3)) || *(p + 4) != '>')
		return (0);
	return ((a->date.year = ft_atoi(p)) < 2017 || a->date.day == 0 ||
		a->date.month == 0 || a->date.day > 31 || a->date.month > 12 ? 0 : 1);
}

static int			fill_author(char *p, t_auth *author)
{
	int			cmp;

	author->date.day = 0;
	author->date.month = 0;
	author->date.year = 0;
	p += 6;
	if (!ft_strnccpy(author->name, p, NAME_BUF_LEN, '\''))
		return (0);
	while (!is_pagin(*p))
		p++;
	p++;
	if ((cmp = ft_strcmp("date=", p)) > -48 || cmp < -57)
		return (cmp == -62 ? 1 : 0);
	return (fill_date(p + 5, author));
}

t_info				*make_info(float ver, char *p, t_elm **grb)
{
	t_info		*ret;
	t_auth		*author;

	if (!(ret = (t_info *)malloc(sizeof(struct s_info))) ||
		!push_elm(ret, 'm', grb))
		return (NULL);
	ret->author = NULL;
	ret->ver = ver;
	while ((p = next_author(p)) && *p)
		if (!*p || ft_strcmp("name=", p) != -39 || !(author = (t_auth *)
			malloc(sizeof(struct s_auth))) || !fill_author(p, author) ||
			!push_elm(author, 'A', &ret->author) || !push_elm(author, 'm', grb))
			return (NULL);
	return (ret);
}
