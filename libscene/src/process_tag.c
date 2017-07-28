/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 14:50:02 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 20:36:55 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

int				process_tag(char *str, t_scn *scn, t_elm **grb)
{
	if (ft_strcmp("cam", str) == -32)
		return (tag_cam(str + 4, scn, grb));
	if (ft_strcmp("lgt", str) == -32)
		return (tag_lgt(str + 4, scn, grb));
	if (ft_strcmp("obj", str) == -32)
		return (tag_obj(str + 4, scn, grb));
	return (0);
}
