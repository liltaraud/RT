/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_skybox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 14:58:22 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/21 15:42:01 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				tag_skybox(char *c, t_scn *s)
{
	char			filename[256];

	if (s->skybox || ft_strcmp("file=", c) != -39)
		return (0);
	c += 6;
	if (!ft_strnccpy(filename, c, 255, '\'') ||
		!(s->skybox = ft_strdup((const char *)filename)))
		return (0);
	return (1);
}
