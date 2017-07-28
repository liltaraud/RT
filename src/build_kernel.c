/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_kernel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:29:53 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/23 15:44:05 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void				print_log(cl_program *pgrm, cl_device_id device)
{
	char				buffer[4096];
	size_t				length;

	clGetProgramBuildInfo(*pgrm, device, CL_PROGRAM_BUILD_LOG, sizeof(buffer),
						buffer, &length);
	ft_putstr(buffer);
	ft_putchar('\n');
	exit(0);
}

cl_kernel				build_kernel(char *kernel_name,
									char *source,
									cl_context *context,
									cl_device_id *device)
{
	char				*ks;
	cl_program			pgrm;
	cl_kernel			kernel;
	cl_int				err;

	ks = load_kernel(source);
	if (!ks)
		return (NULL);
	pgrm = clCreateProgramWithSource(*context, 1, (const char **)&ks,
									NULL, &err);
	if (!pgrm || err != CL_SUCCESS)
	{
		ft_putstr("Couldn't create program from source\n");
		print_log(&pgrm, *device);
	}
	err = clBuildProgram(pgrm, 1, device, "-Werror -g", NULL, NULL);
	free(ks);
	if (err != CL_SUCCESS || !pgrm)
		print_log(&pgrm, *device);
	kernel = clCreateKernel(pgrm, kernel_name, &err);
	return (err != CL_SUCCESS ? NULL : kernel);
}
