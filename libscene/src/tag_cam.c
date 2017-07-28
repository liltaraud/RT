/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_cam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 15:17:30 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 17:38:14 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libscene.h"

static void		static_parse_dim(void **cam, char *c)
{
	float			v[2];

	v[0] = (float)ft_atoi(c);
	if (*c == ':' && !(*cam = NULL))
		return ;
	while (*c && *c != ':')
		if (!ft_isdigit(*(c++)) && !(*cam = NULL))
			return ;
	v[1] = (float)ft_atoi(++c);
	while (*c && *c != '\n' && *c != '\t' && *c != ' ')
		if (!ft_isdigit(*(c++)) && !(*cam = NULL))
			return ;
	if (!*c && !(*cam = NULL))
		return ;
	((t_cam *)*cam)->dimx = v[0];
	((t_cam *)*cam)->dimy = v[1];
}

static void		static_rotate_cam(t_cam *cam)
{
	float			a[3];
	struct s_3v		mark;
	cl_float4		dir;

	mark = cam->mark;
	((float *)&dir)[0] = 0;
	((float *)&dir)[1] = 0;
	((float *)&dir)[2] = 1;
	((float *)&dir)[3] = 1;
	a[0] = ((float *)&cam->dir)[0];
	a[1] = ((float *)&cam->dir)[1];
	a[2] = ((float *)&cam->dir)[2];
	rotate_pt((cl_float4 *)&cam->mark.a, a[0], (cl_float4 *)&mark.b);
	rotate_pt((cl_float4 *)&cam->mark.a, a[0], (cl_float4 *)&mark.c);
	rotate_pt((cl_float4 *)&cam->mark.b, a[1], (cl_float4 *)&mark.a);
	rotate_pt((cl_float4 *)&cam->mark.b, a[1], (cl_float4 *)&mark.c);
	rotate_pt((cl_float4 *)&cam->mark.c, a[2], (cl_float4 *)&mark.a);
	rotate_pt((cl_float4 *)&cam->mark.c, a[2], (cl_float4 *)&mark.b);
	rotate_pt((cl_float4 *)&cam->mark.a, a[0], &dir);
	rotate_pt((cl_float4 *)&cam->mark.b, a[1], &dir);
	rotate_pt((cl_float4 *)&cam->mark.c, a[2], &dir);
	cam->mark = mark;
	cam->dir = dir;
}

static int		static_zero(t_cam *c)
{
	c->name[0] = 'X';
	c->name[1] = '\0';
	((float *)&c->pos)[0] = 0;
	((float *)&c->pos)[1] = 0;
	((float *)&c->pos)[2] = 0;
	((float *)&c->dir)[0] = 0;
	((float *)&c->dir)[1] = 0;
	((float *)&c->dir)[2] = 0;
	c->dimx = MIN_WINX;
	c->dimy = MIN_WINY;
	return (1);
}

static int		static_verify(char *c, t_cam *cam, t_scn *s)
{
	if (!cam)
		return (0);
	if (ft_strcmp("</cam", c) == -62)
	{
		cam->mark = new_mark();
		cam->dimx = cam->dimx < MIN_WINX ? MIN_WINX : cam->dimx;
		cam->dimy = cam->dimy < MIN_WINY ? MIN_WINY : cam->dimy;
		cam->dimx = cam->dimx > MAX_WINX ? MAX_WINX : cam->dimx;
		cam->dimy = cam->dimy > MAX_WINY ? MAX_WINY : cam->dimy;
		cam->dimx += (int)cam->dimx % 2 ? 1 : 0;
		cam->dimy += (int)cam->dimy % 2 ? 1 : 0;
		if (cam->dimx < 0 || cam->dimy < 0)
			return (0);
		static_rotate_cam(cam);
		return (push_elm(cam, 'C', &s->cam));
	}
	return (0);
}

int				tag_cam(char *c, t_scn *s, t_elm **grb)
{
	int				cmp;
	t_cam			*cam;

	if (ft_strcmp("name=", c) != -39 || !(cam = (t_cam *)
		malloc(sizeof(struct s_cam))) || !static_zero(cam) ||
		!push_elm(cam, 'm', grb) || !ft_strnccpy(cam->name, c + 6, NAME_BUF_LEN,
		'\'') || !(c = ft_strchr(c + 6, '\'')) || *(c + 1) != '>' ||
		!*(c = c + 2))
		return (0);
	while ((c = scn_jmp_next_line(c)) && *c != '<' && cam)
	{
		if (((cmp = ft_strcmp("pos=", c)) <= -48 && cmp >= -57) || cmp == -45)
			cam->pos = scn_parse_float4(c + 4, (void **)&cam);
		else if (((cmp = ft_strcmp("rot=", c)) <= -48 && cmp >= -57) ||
				cmp == -45)
			cam->dir = scn_parse_float4(c + 4, (void **)&cam);
		else if ((cmp = ft_strcmp("dim=", c)) <= -48 && cmp >= -57)
			static_parse_dim((void **)&cam, c + 4);
		else
			return (0);
	}
	return (static_verify(c, cam, s));
}
