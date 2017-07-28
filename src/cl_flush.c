/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_flush.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:36:34 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/24 16:36:35 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				cl_flush(t_rt *r)
{
	if (r->cl)
	{
		if (r->cl->cmd_queue)
		{
			clFlush(r->cl->cmd_queue);
			clFinish(r->cl->cmd_queue);
		}
		if (r->cl->cmd_queue)
			clReleaseCommandQueue(r->cl->cmd_queue);
		if (r->cl->context)
			clReleaseContext(r->cl->context);
		if (r->cl->k_lighting)
			clReleaseKernel(r->cl->k_lighting);
		clReleaseMemObject(r->cl->k_data_skybox);
	}
	free(r->cl);
}
