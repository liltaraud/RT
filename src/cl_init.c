/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:44:17 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/21 14:40:53 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		kernel_compile(t_rt *r)
{
	r->cl->k_lighting = build_kernel("render",
									"./kernels/GPU_render_raytraced.cl",
									&r->cl->context, &r->cl->device_id);
	if (r->cl->k_lighting == NULL)
		terminate(r, 0);
}

int				cl_init(t_rt *r)
{
	cl_int						err;
	cl_context_properties		context_properties[3];

	context_properties[0] = CL_CONTEXT_PLATFORM;
	context_properties[1] = 0;
	context_properties[2] = 0;
	if (!(r->cl = (t_opencl *)ft_memalloc(sizeof(t_opencl))))
		terminate(r, "Malloc error\n");
	err = clGetPlatformIDs(1, &r->cl->platform_id, &r->cl->num_platforms);
	if (r->cl->num_platforms <= 0)
		terminate(r, "No plateform available\n");
	context_properties[1] = (cl_context_properties)r->cl->platform_id;
	r->cl->context = clCreateContextFromType(context_properties,
					CL_DEVICE_TYPE_GPU, &ocl_context_callback, (void *)r, &err);
	check_ocl_error(err, r);
	err = clGetDeviceIDs(r->cl->platform_id, CL_DEVICE_TYPE_GPU, 1,
					&r->cl->device_id, &r->cl->num_devices);
	check_ocl_error(err, r);
	r->cl->cmd_queue = clCreateCommandQueue(r->cl->context, r->cl->device_id,
					0, &err);
	check_ocl_error(err, r);
	kernel_compile(r);
	cl_objects_init(r);
	return (0);
}
