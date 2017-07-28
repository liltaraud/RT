/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcaspar <hcaspar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:23:23 by hcaspar           #+#    #+#             */
/*   Updated: 2017/05/22 18:24:03 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					interface_move(int x, t_rt *r)
{
	if (x < r->gui.filter.line_pos_start.x)
		x = r->gui.filter.line_pos_start.x;
	if (x > r->gui.filter.line_pos_end.x - 25)
		x = r->gui.filter.line_pos_end.x - 25;
	if (r->gui.filter.state)
	{
		r->gui.filter.value = ((x - r->gui.filter.line_pos_start.x) / 33) * 33;
		r->filter = r->gui.filter.value / 33;
		r->gui.filter.name = r->gui.texte[r->filter + 1];
	}
	return (1);
}
