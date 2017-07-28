/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 09:47:15 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/23 16:20:34 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			main(int ac, char **av)
{
	t_rt	r;

	ft_bzero(&r, sizeof(t_rt));
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		exit(0);
	if (ac != 2 || !initialization(&r, av[1]))
	{
		ft_putendl(ac != 2 ? "Usage : ./rt <path/scene.rt>" :
						"Error : bad scene/obj/mtl/bmp file.");
		return (1);
	}
	r.filter = 0;
	r.enable_skybox = 1;
	sdl_init(&r);
	gui_init(&r);
	interface_draw(&r);
	cl_init(&r);
	skybox_init(&r);
	sdl_loop(&r);
	return (0);
}
