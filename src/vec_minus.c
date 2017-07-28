/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_minus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 21:05:11 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/09 21:01:08 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec			vec_minus(t_vec a, t_vec b)
{
	t_vec		res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec			vec_minus_i(t_vec a, const cl_float b)
{
	t_vec		res;

	res.x = a.x - b;
	res.y = a.y - b;
	res.z = a.z - b;
	return (res);
}
