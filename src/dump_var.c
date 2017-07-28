/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 17:05:14 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/22 17:26:13 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			dump_var(t_rt *r, t_scn *s)
{
	if (!s)
		return ;
	r->obj_data_size = s->ods;
	r->obj_data_table_size = s->odts;
	r->light_data_size = s->lds;
	r->light_table_size = s->lts;
	r->obj_data = s->od;
	r->obj_data_table = s->ot;
	r->light_data = s->ld;
	r->light_data_table = s->lt;
	r->curcam = (t_cam *)s->cam->elm;
}
