/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_write_tables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 15:53:33 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/14 18:37:51 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cl_renew_light_table(t_rt *r)
{
	cl_int	err;

	r->cl->k_data_light_table = clCreateBuffer(r->cl->context,
							CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
							r->light_table_size * sizeof(cl_int),
							r->light_data_table, &err);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_light_table,
						CL_TRUE, 0, r->light_table_size * sizeof(cl_int),
						r->light_data_table, 0, NULL, NULL);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 5, sizeof(cl_mem),
						(void *)&r->cl->k_data_light_table);
	check_ocl_error(err, r);
}

void		cl_renew_obj_table(t_rt *r)
{
	cl_int	err;

	r->cl->k_data_obj_table = clCreateBuffer(r->cl->context,
							CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
							r->obj_data_table_size * sizeof(cl_int),
							r->obj_data_table, &err);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_obj_table,
						CL_TRUE, 0, r->obj_data_table_size * sizeof(cl_int),
						r->obj_data_table, 0, NULL, NULL);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 3, sizeof(cl_mem),
						(void *)&r->cl->k_data_obj_table);
	check_ocl_error(err, r);
}

void		cl_write_tables(t_rt *r)
{
	if (r->cl->k_data_obj_table)
	{
		clReleaseMemObject(r->cl->k_data_obj_table);
		cl_renew_obj_table(r);
	}
	if (r->cl->k_data_light_table)
	{
		clReleaseMemObject(r->cl->k_data_light_table);
		cl_renew_light_table(r);
	}
}
