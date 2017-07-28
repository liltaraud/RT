/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libscene.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttrossea <ttrossea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 12:43:03 by ttrossea          #+#    #+#             */
/*   Updated: 2017/05/23 21:56:36 by ttrossea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSCENE_H
# define LIBSCENE_H
# include <unistd.h>
# include <math.h>
# include "SDL.h"
# include "libft.h"

# ifdef __APPLE__
#  include <OpenCL/cl_platform.h>
# else
#  include <CL/cl_platform.h>
# endif

# define LGT_SUN					1
# define LGT_SPT					2

# define ATT_LIN					1
# define ATT_QUD					2
# define ATT_MIX					3

# define OBJ_SPHERE					1
# define OBJ_PLANE					2
# define OBJ_CONE					3
# define OBJ_CYLINDRE				4
# define OBJ_PARABOLOID				5

# define MIN_WINX					350
# define MIN_WINY					200
# define MAX_WINX					12000
# define MAX_WINY					6000

# define NAME_BUF_LEN				32

typedef struct		s_date
{
	uint			day;
	uint			month;
	uint			year;
}					t_date;

typedef struct		s_auth
{
	char			name[NAME_BUF_LEN];
	struct s_date	date;
}					t_auth;

typedef struct		s_info
{
	float			ver;
	t_elm			*author;
}					t_info;

typedef struct		s_3v
{
	float			a[3];
	float			b[3];
	float			c[3];
}					t_3v;

typedef struct		s_cam
{
	char			name[NAME_BUF_LEN];
	cl_float4		pos;
	cl_float4		dir;
	float			dimx;
	float			dimy;
	struct s_3v		mark;
}					t_cam;

typedef struct		s_mtl
{
	cl_float		ns;
	cl_float		ni;
	cl_float		ke;
	cl_float4		kd;
}					t_mtl;

typedef struct		s_sphere
{
	float			ray;
}					t_sphere;

typedef struct		s_cylindre
{
	float			ray;
	cl_float4		dir;
}					t_cylindre;

typedef struct		s_paraboloid
{
	float			ray;
	cl_float4		dir;
}					t_paraboloid;

typedef struct		s_cone
{
	float			angle;
	cl_float4		dir;
}					t_cone;

typedef struct		s_plane
{
	cl_float4		dir;
}					t_plane;

typedef struct		s_object
{
	struct s_mtl	mtl;

	uint			id;
	cl_int			buf_offset;
	char			name[NAME_BUF_LEN];
	char			type;
	cl_float4		pos;

	cl_float4		rot;
	struct s_3v		mark;

	void			*content;
}					t_object;

typedef struct		s_lgt
{
	char			name[NAME_BUF_LEN];
	char			type;
	cl_int			buf_offset;

	cl_float4		pos;
	cl_float4		dir;
	cl_float4		unit_color;
	float			intensity;
}					t_lgt;

typedef struct		s_scn
{
	t_info			*info;

	size_t			nobj;
	char			name[NAME_BUF_LEN];
	t_elm			*cam;
	t_elm			*obj;
	t_elm			*lgt;

	t_elm			*grb;

	int				skybool;
	cl_int			ods;
	cl_int			odts;
	cl_int			lds;
	cl_int			lts;
	cl_float		*od;
	cl_int			*ot;
	cl_float		*ld;
	cl_int			*lt;
}					t_scn;

char				*scn_jmp_next_line(char *ptr);
t_elm				*parse_scene_file(char *filename);
t_info				*make_info(float ver, char *p, t_elm **grb);
t_scn				*new_scene(char *s, t_info *info, t_elm **grb);
int					process_tag(char *str, t_scn *scn, t_elm **grb);
int					tag_skybox(char *c, t_scn *s);
int					tag_cam(char *c, t_scn *s, t_elm **grb);
int					tag_lgt(char *c, t_scn *s, t_elm **grb);
int					tag_sound(char *c, t_scn *s, t_elm **grb);
int					tag_obj(char *c, t_scn *s, t_elm **grb);
int					tag_loadmtl(char *c, t_scn *s, t_elm **grb);
int					object_sphere(char *c, t_object *o, t_elm **grb);
int					object_cone(char *c, t_object *o, t_elm **grb);
int					object_cylindre(char *c, t_object *o, t_elm **grb);
int					object_paraboloid(char *c, t_object *o, t_elm **grb);
int					object_plane(t_object *o, t_elm **grb);
cl_float4			scn_parse_float4(char *c, void **nulliferr);
int					scn_parse_float(char *c, float *val);
t_3v				new_mark(void);
void				rotate_pt(cl_float4 *ax, float angle, cl_float4 *pt);
int					init_mtl(t_mtl *m);
int					verify_mtl(t_mtl *m);
void				free_scene(t_scn *s);

#endif
