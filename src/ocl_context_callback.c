/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_context_callback.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:22:30 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/24 15:12:49 by ltaraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ocl_context_callback(const char *errinfo,
									const void *private_info,
									size_t cb,
									void *user_data)
{
	ft_putstr(errinfo);
	if (private_info == NULL)
		ft_putstr("NULL PRIVATE INFO \n");
	if (user_data == NULL)
		ft_putstr("NULL_USER_DATA \n");
	cb++;
	exit(0);
}
