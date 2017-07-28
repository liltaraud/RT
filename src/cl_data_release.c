/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_data_release.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 13:45:16 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/21 14:25:19 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cl_data_release(t_rt *r)
{
	clReleaseMemObject(r->cl->k_data_image);
	clReleaseMemObject(r->cl->k_data_info);
	clReleaseMemObject(r->cl->k_data_obj_table);
	clReleaseMemObject(r->cl->k_data_obj);
	clReleaseMemObject(r->cl->k_data_light_table);
	clReleaseMemObject(r->cl->k_data_light);
}
