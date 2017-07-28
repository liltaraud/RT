/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_sound.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 19:00:39 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/21 15:02:09 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				tag_sound(char *c, t_scn *s, t_elm **grb)
{
	char		*bf;

	if (ft_strcmp("file=", c) != 39 || !(bf = (char *)malloc(sizeof(char) *
		NAME_BUF_LEN)) || !ft_strnccpy(bf, c + 6, NAME_BUF_LEN, '\'') ||
		!(c = ft_strchr(c + 6, '\'')) || *(c + 1) != '>' ||
		!*(c = c + 2))
		return (0);
	return (!push_elm(bf, 's', &s->sounds) || !push_elm(bf, 'm', grb) ? 0 : 1);
}
