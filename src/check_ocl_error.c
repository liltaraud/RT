/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ocl_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 15:31:42 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/09 20:59:31 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_ocl_error(cl_int err, t_rt *r)
{
	if (err != CL_SUCCESS)
	{
		ft_putstr("OpenCL returned an error ! Error code = ");
		ft_putnbr(err);
		terminate(r, "\n");
	}
}
