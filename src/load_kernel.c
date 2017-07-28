/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 15:56:39 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/09 21:00:19 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			*load_kernel(char *filepath)
{
	char		*kernel;

	kernel = ft_read_file(filepath);
	return (kernel);
}
