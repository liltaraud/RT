/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_div_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 21:16:49 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/09 21:01:00 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec		vec_div_i(t_vec a, const cl_float n)
{
	t_vec	res;

	if (n)
	{
		res.x = a.x / (cl_float)n;
		res.y = a.y / (cl_float)n;
		res.z = a.z / (cl_float)n;
	}
	else
	{
		res.x = 0.0f;
		res.y = 0.0f;
		res.z = 0.0f;
	}
	return (res);
}
