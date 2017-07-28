/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltaraud <ltaraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 09:48:04 by ltaraud           #+#    #+#             */
/*   Updated: 2017/05/24 16:51:43 by hcaspar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>
# include "SDL.h"
# include <SDL/SDL_ttf.h>

# include "keys.h"
# include "libscene.h"

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define SKYBOX 0
# define NO_FILTER 1
# define SEPIA 2
# define GRAYSCALE 3
# define CELSHADE 4

# define ENABLED 1
# define DISABLED 0

# define FULLSCREEN_MAC_SIZE_X 2560
# define FULLSCREEN_MAC_SIZE_Y 1440

# define MENU_BAR_H 100

# define SZ_MTL 7
# define N NAME

# define SZ_SPHERE 11
# define SZ_PLANE 13
# define SZ_CONE 14
# define SZ_CYLINDRE 14
# define SZ_PARABOLOID 14

# define SZ_SUN 7
# define SZ_SPT 10

# define POINT_LIGHT 0
# define SPOT_LIGHT 1
# define SPHERE 1
# define PLANE 2
# define CONE 3
# define CYLINDRE 4
# define PARABOLOID 5

typedef struct			s_vec
{
	cl_float			x;
	cl_float			y;
	cl_float			z;
}						t_vec;

typedef struct			s_camera
{
	t_vec				u;
	t_vec				v;
	t_vec				w;
	t_vec				dir;
	t_vec				pos;
	cl_int				h_fov;
	cl_int				v_fov;
}						t_camera;

typedef struct			s_checkbox
{
	SDL_Rect			box_pos_start;
	SDL_Rect			box_pos_end;
	int					state;
	SDL_Rect			name_pos;
	SDL_Surface			*name;
}						t_checkbox;

typedef struct			s_scrollbar
{
	SDL_Rect			line_pos_start;
	SDL_Rect			line_pos_end;
	unsigned int		color_line;
	unsigned int		color_cursor;
	int					state;
	int					value;
	SDL_Surface			*name;
	SDL_Rect			name_pos;
}						t_scrollbar;

typedef struct			s_scene_info
{
	SDL_Rect			scn_pos;
	SDL_Rect			cam_pos;
	SDL_Surface			*scn;
	SDL_Surface			*cam;
}						t_scene_info;

typedef struct			s_gui
{
	SDL_Surface			*bmp[2];
	SDL_Surface			*texte[5];
	t_checkbox			skybox;
	t_scrollbar			filter;
	t_scene_info		scene_info;
}						t_gui;

typedef struct			s_sdl
{
	SDL_Window			*p_win;
	SDL_Event			event;
	SDL_Surface			*screen;
	SDL_Rect			image_pos;
	TTF_Font			*police;
	SDL_Color			color;
	SDL_Surface			*skybox;
	int					keystate[9];
	int					is_key_pressed;
	int					mousestate[3];
	int					fullscreen;
}						t_sdl;

typedef struct			s_opencl
{
	size_t				gws;
	size_t				lws;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	cmd_queue;
	cl_mem				k_data_image;
	cl_mem				k_data_obj;
	cl_mem				k_data_obj_table;
	cl_mem				k_data_light;
	cl_mem				k_data_light_table;
	cl_mem				k_data_info;
	cl_mem				k_data_skybox;
	cl_platform_id		platform_id;
	cl_uint				num_devices;
	cl_uint				num_platforms;
	cl_int				err;
	cl_kernel			k_buffering;
	cl_kernel			k_lighting;
}						t_opencl;

typedef struct			s_ts
{
	float				center;
	float				radius;
	float				v1;
	float				v2;
	float				v3;
	float				e1;
	float				e2;
	float				t;
	float				e;
	float				v;
	float				va;
	float				vb;
	float				vc;
	float				vbb;
	float				vbc;
	float				vcc;
	float				ab;
	float				bc;
	float				ca;
	float				d1;
	float				d2;
	float				d3;
	float				m1;
	float				m2;
	float				m3;
	float				q1;
	float				q2;
	float				q3;
	float				qc;
	float				qa;
	float				qb;
}						t_ts;

typedef struct			s_rt
{
	t_sdl				sdl;
	t_gui				gui;
	float				oldtime;
	cl_float			info[18];
	cl_int				enable_skybox;
	size_t				gws[2];
	size_t				lws[2];
	t_opencl			*cl;
	char				*win_title;
	cl_int				size_x;
	cl_int				size_y;
	cl_int				obj_data_size;
	cl_int				obj_data_table_size;
	cl_int				light_data_size;
	cl_int				light_table_size;
	cl_float			*obj_data;
	cl_int				*obj_data_table;
	cl_float			*light_data;
	cl_int				*light_data_table;
	cl_int				filter;
	t_camera			cam;
	t_ts				ts;
	int					nobj;
	t_elm				*scnstk;
	t_scn				*scn;
	t_cam				*curcam;
}						t_rt;

cl_float4				vec_float4(t_vec v);
t_vec					float4_vec(cl_float4 f);
int						camera_init(t_rt *r, t_cam *c);
int						switch_env(t_rt *r, int key, int event);
int						manage_cam_scn(t_rt *r, SDL_Keycode key, int type);
void					dump_var(t_rt *r, t_scn *s);

void					sdl_hook(t_rt *r, SDL_Event event);
void					sdl_init(t_rt *r);
void					sdl_loop(t_rt *r);

void					widgets_add(t_rt *r);

void					interface_draw(t_rt *r);
int						interface_move(int x, t_rt *r);

void					gui_draw(t_rt *r);
void					gui_init(t_rt *r);

void					skybox_init(t_rt *r);

void					mouse_camera(t_rt *r, int x, int y);
int						key_press(SDL_Keycode key, t_rt *r);
int						key_release(SDL_Keycode key, t_rt *r);
int						mouse_hook_down(int x, int y, t_rt *r);
int						mouse_hook_up(t_rt *r);

void					rot_x(t_rt *r, int v);
void					rot_y(t_rt *r, int v);
void					rot_z(t_rt *r, int v);

t_vec					vec_opposite(t_vec a);
t_vec					vec_plus(t_vec a, t_vec b);
cl_float				vec_dot(t_vec a, t_vec b);
cl_float				vec_length(t_vec a);
t_vec					vec_minus(t_vec a, t_vec b);
t_vec					vec_minus_i(t_vec a, const cl_float b);
t_vec					vec_div_i(t_vec a, const cl_float n);
t_vec					vec_cross(t_vec a, t_vec b);
t_vec					vec_times_i(t_vec a, const cl_float n);
t_vec					vec_normalize(t_vec a);

void					terminate(t_rt *r, char *msg);

char					*load_kernel(char *filepath);
int						cl_init(t_rt *r);
void					cl_flush(t_rt *r);
void					check_ocl_error(cl_int err, t_rt *r);
cl_kernel				build_kernel(char *kernel_name, char *source, \
						cl_context *context, cl_device_id *device);
void					ocl_context_callback(const char *errinfo, \
						const void *private_info, size_t cb, void *user_data);
void					cl_objects_init(t_rt *r);
int						initialization(t_rt *r, char *scenepath);
int						obj_init(t_scn *s);
size_t					obj_dump(t_object *o, cl_float *p, cl_int *offset);
int						obj_table_init(t_scn *s);
int						lgt_init(t_scn *s);
int						lgt_table_init(t_scn *s);

void					render(t_rt *r);

void					cl_write_tables(t_rt *r);
void					cl_update_camera(t_rt *r);
void					cl_data_release(t_rt *r);
void					cl_get_ws(t_rt *r);

void					animate(t_rt *r);

#endif
