/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 21:12:20 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/09 21:01:05 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float			vec_length(t_vec a)
{
	return (sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
}
