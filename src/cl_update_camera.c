/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_update_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 14:23:04 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/22 13:43:51 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cam_dir(t_rt *r)
{
	cl_float	half_w;
	cl_float	half_h;
	cl_float	w_coef;

	half_w = r->size_x / (cl_float)2.0;
	half_h = r->size_y / (cl_float)2.0;
	w_coef = half_h / (float)tan(0.65 * 0.5);
	r->cam.w = vec_times_i(r->cam.u, -half_w);
	r->cam.w = vec_plus(r->cam.w, vec_times_i(r->cam.v, half_h));
	r->cam.w = vec_plus(r->cam.w, vec_times_i(r->cam.dir, w_coef));
}

static void		update_data(t_rt *r)
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

void			cl_update_camera(t_rt *r)
{
	cl_int	err;

	cam_dir(r);
	update_data(r);
	clReleaseMemObject(r->cl->k_data_info);
	r->cl->k_data_info = clCreateBuffer(r->cl->context, CL_MEM_READ_WRITE,
						18 * sizeof(cl_float), NULL, &err);
	check_ocl_error(err, r);
	err = clEnqueueWriteBuffer(r->cl->cmd_queue, r->cl->k_data_info, CL_TRUE, 0,
						18 * sizeof(cl_float), r->info, 0, NULL, NULL);
	check_ocl_error(err, r);
	err = clSetKernelArg(r->cl->k_lighting, 0, sizeof(cl_mem),
						(void *)&r->cl->k_data_info);
	check_ocl_error(err, r);
}
