/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_objects_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 14:48:36 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/22 13:41:54 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		fill_tab(t_rt *r)
{
	r->info[0] = (cl_float)r->cam.pos.x;
	r->info[1] = (cl_float)r->cam.pos.y;
	r->info[2] = (cl_float)r->cam.pos.z;
	r->info[3] = (cl_float)r->cam.w.x;
	r->info[4] = (cl_float)r->cam.w.y;
	r->info[5] = (cl_float)r->cam.w.z;
	r->info[6] = (cl_float)r->cam.u.x;
	r->info[7] = (cl_float)r->cam.u.y;
	r->info[8] = (cl_float)r->cam.u.z;
	r->info[9] = (cl_float)r->cam.v.x;
	r->info[10] = (cl_float)r->cam.v.y;
	r->info[11] = (cl_float)r->cam.v.z;
	r->info[12] = (cl_float)r->size_x;
	r->info[13] = (cl_float)r->size_y;
	r->info[14] = (cl_float)r->filter;
	r->info[15] = (cl_float)r->enable_skybox;
	r->info[16] = (cl_float)r->sdl.skybox->w;
	r->info[17] = (cl_float)r->sdl.skybox->h;
}

static void		cl_create_objects(t_rt *r, cl_int res)
{
	cl_int		err;

	r->cl->k_data_image = clCreateBuffer(r->cl->context, CL_MEM_READ_WRITE,
									res * sizeof(cl_uint), NULL, &err);
	check_ocl_error(err, r);
	r->cl->k_data_info = clCreateBuffer(r->cl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, 18 * sizeof(cl_float), r->info,
		&err);
	check_ocl_error(err, r);
	r->cl->k_data_obj = clCreateBuffer(r->cl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		r->obj_data_size * sizeof(cl_float), r->obj_data, &err);
	check_ocl_error(err, r);
	r->cl->k_data_obj_table = clCreateBuffer(r->cl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		r->obj_data_table_size * sizeof(cl_int), r->obj_data_table, &err);
	check_ocl_error(err, r);
	r->cl->k_data_light = clCreateBuffer(r->cl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		r->light_data_size * sizeof(cl_float), r->light_data, &err);
	check_ocl_error(err, r);
	r->cl->k_data_light_table = clCreateBuffer(r->cl->context,
		CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,
		r->light_data_size * sizeof(cl_int), r->light_data_table, &err);
}

static void		cl_set_kernels_args(t_rt *r)
{
	cl_int		err;
	cl_int		mem_size;

	mem_size = sizeof(cl_mem);
	err = clSetKernelArg(r->cl->k_lighting, 0, mem_size,
						(void *)&r->cl->k_data_info);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 1, mem_size,
						(void *)&r->cl->k_data_image);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 2, mem_size,
						(void *)&r->cl->k_data_obj);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 3, mem_size,
						(void *)&r->cl->k_data_obj_table);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 4, mem_size,
						(void *)&r->cl->k_data_light);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 5, mem_size,
						(void *)&r->cl->k_data_light_table);
	check_ocl_error(err, r);
}

static void		cl_write_objects(t_rt *r)
{
	cl_int		err;

	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_info, CL_TRUE, 0,
						18 * sizeof(cl_float), r->info, 0, NULL, NULL);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_obj, CL_TRUE, 0,
						r->obj_data_size * sizeof(cl_float), r->obj_data,
						0, NULL, NULL);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_obj_table,
						CL_TRUE, 0, r->obj_data_table_size * sizeof(cl_int),
						r->obj_data_table, 0, NULL, NULL);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_light, CL_TRUE,
						0, r->light_data_size * sizeof(cl_float), r->light_data,
						0, NULL, NULL);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_light_table,
						CL_TRUE, 0, r->light_table_size * sizeof(cl_int),
						r->light_data_table, 0, NULL, NULL);
	check_ocl_error(err, r);
}

void			cl_objects_init(t_rt *r)
{
	cl_int		res;

	res = r->size_x * r->size_y;
	cl_get_ws(r);
	cl_create_objects(r, res);
	fill_tab(r);
	cl_write_objects(r);
	cl_set_kernels_args(r);
}
