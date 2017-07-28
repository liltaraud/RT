#define SPHERE 1
#define PLANE 2
#define CONE 3
#define CYLINDER 4
#define PARABOLOID 5
#define TRIANGLE 6

#define SEPIA 1
#define GRAYSCALE 2
#define CELSHADE 3

#define OFST 9

#define GLASS_IOR 1.5
#define WATER_IOR 1.2
#define DIAM_IOR 1.8

#define RAD_UNIT 0.636618
#define TAB_OFFSET 2
#define	EPS 0.00001
#define MAX_DEPTH 99999999
#define MIN_DIST 0.2f
#define PI 3.14159
#define SCOEF 0.90412

typedef struct		s_ray
{
	float3			o;
	float3			dir;
	float3			normal;
	float3			color;
	float			t;
	float4			att;
	int				id;
}					t_ray;

typedef struct		s_pt_light
{
	float3			pos;
	float3			color;
	float3			power;
}					t_pt_light;

typedef struct		s_cam
{
	float3			pos;
	float3			u;
	float3			v;
	float3			w;
}					t_cam;

typedef struct		s_data
{
	__global float	*obj;
	__global int	*obj_t;
	__global float	*light;
	__global int	*light_t;
	__global uint	*skybox;
	int2			res;
	const int		gid;
	const int		skbx_enable;
}					t_data;

typedef struct		s_brdf
{
	float3			p;
	float3			n;
	float3			v;
	float3			l;
	float3			light_color;
	float3			light_pos;
	float			light_pow;
	float			light_dist;
	float4			att;
	int				id;
	t_data			d;
}					t_brdf;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

__inline float3	reflect(const float3	i,
						const float3	n)
{
	return (i - n * 2.0f * dot(i, n));
}

__inline void	triangle_intersect(	t_ray			*r,
									const int		id,
									t_data			d)
{
	const float		nseg = d.obj[id + 7];

	for (int i = 0; i < nseg; i++){
		const float3	v1 = (float3){d.obj[id + i * OFST + 8], d.obj[id + i * OFST + 9], d.obj[id + i * OFST + 10]};
		const float3	v2 = (float3){d.obj[id + i * OFST + 11], d.obj[id + i * OFST + 12], d.obj[id + i * OFST + 13]};
		const float3	v3 = (float3){d.obj[id + i * OFST + 14], d.obj[id + i * OFST + 15], d.obj[id + i * OFST + 16]};
		const float3	e1 = v2 - v1;
		const float3	e2 = v3 - v1;
		const float3	p = cross(r->dir, e2);
		const float		det = dot(p, e1);

		if (det < -0.00001f || det > 0.00001f)
		{
			const float		idet = 1.0 / (float)det;
			const float3	t_vec = r->o - v1;
			const float3	q = cross(t_vec, e1);
			const float		u = dot(p, t_vec) * idet;
			const float		v = dot(q, r->dir) * idet;
			const float		t_dist = dot(q, e2) * idet;
			if (u >= 0 && v >= 0 && u + v <= 1 && t_dist > MIN_DIST && t_dist < r->t)
			{
				r->t = t_dist;
				r->id = id;
				const float3  n = cross(e1, e2);
				r->normal = dot(n , r->dir) > 0.0 ? normalize(n) : normalize(-n);
			}
		}
	}
}

__inline void	cylinder_intersect( t_ray			*r,
									const int 		id,
									t_data			d)
{
	const float3	center = {d.obj[id + 7], d.obj[id + 8], d.obj[id + 9]};
	const float3	dir = {d.obj[id + 10], d.obj[id + 11], d.obj[id + 12]};
	const float		radius = d.obj[id + 13];
	float 			t, t0 ,t1 = 0.0;
	float 			tmp = dot(r->dir, dir);
	float 			tmp2 = dot(r->o - center, dir);

	float 			a = dot(r->dir, r->dir) - (tmp * tmp);
	float 			b = 2 * (dot(r->dir, r->o - center) - (tmp * tmp2));
	float 			c = dot(r->o - center, r->o - center) - (tmp2 * tmp2) - (radius * radius);
	float 			delta = b * b - 4.0f * a * c;

	if (delta >= 0)
	{
		if (delta == 0)
			t = (-b) / (2 * a);
		delta = sqrt(delta);
		t0 = (-b + delta) / (2 * a);
		t1 = (-b - delta) / (2 * a);
		t = (t0 < t1) ? t0 : t1;
	}

	if (t > MIN_DIST && t < r->t)
	{
		r->t = t;
		r->id = id;
		float 			m = dot(r->dir, dir * t) + dot(r->o - center, dir);
		r->normal = normalize((r->o + r->dir * t) - center - dir * (m));
	}
}

__inline void      paraboloid_intersect(		t_ray*			r,
												const int		id,
												t_data			d)
{
	const float3	center = {d.obj[id + 7], d.obj[id + 8], d.obj[id + 9]};
	const float3	dir = {d.obj[id + 10], d.obj[id + 11], d.obj[id + 12]};
	const float		radius = d.obj[id + 13];
	float 			t, t0, t1 = 0.0;
	float 			tmp = dot(r->dir, dir);
	float 			tmp2 = dot(r->o - center, dir);

	float 			a = dot(r->dir, r->dir) - (tmp * tmp);
	float 			b = 2 * (dot(r->dir, r->o - center) - tmp * (tmp2 + 2.0f * radius));
	float 			c = dot(r->o - center, r->o - center) - tmp2 * (tmp2 + 4.0f * radius);
	float 			delta = b * b - 4.0f * a * c;

	if (delta >= 0)
	{
		if (delta == 0)
			t = (-b) / (2 * a);
		delta = sqrt(delta);
		t0 = (-b + delta) / (2 * a);
		t1 = (-b - delta) / (2 * a);
		t = (t0 < t1) ? t0 : t1;
	}

	float 			m = dot(r->dir, dir * t) + dot(r->o - center, dir);
	if (t > MIN_DIST && t < r->t)
	{
		r->t = t;
		r->id = id;
		r->normal = normalize((r->o + r->dir * t) - center - dir * ((m) + radius));
	}
}

__inline void      cone_intersect(		t_ray*			r,
										const int		id,
										t_data			d)
{
	const float3	center = {d.obj[id + 7], d.obj[id + 8], d.obj[id + 9]};
	const float3	dir = {d.obj[id + 10], d.obj[id + 11], d.obj[id + 12]};
	const float		radius = d.obj[id + 13];
	float 			t, t0, t1 = 0.0;
	float 			p = (1.0f + pow((float)tan(radius * (3.141592f) / 180.0f), 2));
	float 			tmp = dot(r->dir, dir);
	float 			tmp2 = dot(r->o - center, dir);

	float 			a = dot(r->dir, r->dir) - (p * (tmp * tmp));
	float 			b = 2 * (dot(r->dir, r->o - center) - (p * tmp * tmp2));
	float 			c = dot(r->o - center, r->o - center) - (p * tmp2 * tmp2);
	float 			delta = b * b - 4.0f * a * c;

	if (delta > 0)
	{
		if (delta == 0)
			t = (-b) / (2 * a);
		delta = sqrt(delta);
		t0 = (-b + delta) / (2 * a);
		t1 = (-b - delta) / (2 * a);
		t = (t0 < t1) ? t0 : t1;
	}

	float 			m = dot(r->dir, dir * t) + dot(r->o - center, dir);
	if (t > MIN_DIST && t < r->t)
	{
		r->t = t;
		r->id = id;
		r->normal = normalize((r->o + r->dir * t) - center - p * dir * (m));
	}
}

__inline void	plane_intersect(	t_ray*			r,
									const int		id,
									t_data			d)
{
	const float3	pos = {d.obj[id + 7], d.obj[id + 8], d.obj[id + 9]};
	const float3	plane_n = {d.obj[id + 10], d.obj[id + 11], d.obj[id + 12]};
	const float		denom = dot(plane_n, r->dir);

	if (fabs(denom) > 0.00001)
	{
		const float	t = dot((pos - r->o), plane_n) / (float)denom;
		if (t < r->t && t > MIN_DIST && t < MAX_DEPTH)
		{
			r->t = t;
			r->id = id;
			if (denom > 0.0f)
				r->normal = -plane_n;
			else
				r->normal = plane_n;
		}
	}
}

__inline void	sphere_intersect(	t_ray*			r,
									const int		id,
									t_data			d)
{
	float3		sph_pos = {d.obj[id + 7], d.obj[id + 8], d.obj[id + 9]};
	float		radius = d.obj[id + 10];
	float3		l = sph_pos - r->o;
	float		tca = dot(l, r->dir);

	if (tca >= 0)
	{
		const	float d = sqrt(dot(l, l) - dot(tca, tca));
		if (d >= 0 && d <= radius)
		{
			float thc = sqrt(radius * radius - dot(d, d));
			float t0 = tca - thc;
			float t1 = tca + thc;
			float t = (t0 < t1) ? t0 : t1;
			if (t < r->t && t < MAX_DEPTH)
			{
				r->t = t;
				r->id = id;
				r->normal = normalize((r->o + r->dir * t) - sph_pos);
			}
		}
	}

}

__inline void	intersect(		t_ray*			r,
								const int		id,
								const int		obj_type,
								t_data			d)
{
	if (obj_type == SPHERE)
		sphere_intersect(r, id, d);
	if (obj_type == PLANE)
		plane_intersect(r, id, d);
	if (obj_type == TRIANGLE)
		triangle_intersect(r, id, d);
	if (obj_type == CYLINDER)
		cylinder_intersect(r, id, d);
	if (obj_type == CONE)
		cone_intersect(r, id, d);
	if (obj_type == PARABOLOID)
		paraboloid_intersect(r, id, d);
}

__inline float	check_hit(t_ray* r, t_data d)
{
	int		total_obj = d.obj_t[0];
	int		id;

	r->t = MAX_DEPTH;
	for (int i = 0; i < total_obj; i++){ // We intersect all objects
		id = d.obj_t[i * 2 + 1];
		intersect(r, id, d.obj_t[i * 2 + 2], d);
	}
	if (r->t < MAX_DEPTH)
	{
		r->att.x = d.obj[r->id + 3]; // If we have found an object, we copy its
		r->att.y = d.obj[r->id + 4]; // attributes in the ray structure
		r->att.z = d.obj[r->id + 5];
		r->att.w = d.obj[r->id + 6];
		r->color = (float3)(d.obj[r->id], d.obj[r->id + 1], d.obj[r->id + 2]);
	}
	return (r->t);
}

__inline float schlick_fresnel(	const float3	h_vec,
								const float		ref,
								const float3	cam_dir)
{
	return (ref + (1.0 - ref) * pow((1.0 - dot(h_vec, cam_dir)), 5.0));
}

__inline float tr_ggx(	const float 	r_sq,
						const float		n_h)
{
	const float g = PI * powf(n_h * n_h * (r_sq  - 1.0) + 1.0, 2.0);

	return (r_sq / (float)g);
}
__inline float	geometrical_shadowing(	const float		n_h,
										const float		n_v,
										const float		n_l,
										const float		v_h,
										const float		l_h)
{
	float	a = (2.0f * n_h * n_v) / (float)v_h;
	float	b = (2.0f * n_h * n_l) / (float)v_h;

	return (min(1.0f, min(a, b)));
}

__inline float	ggx_specular(	const float3	l,
								const float3	li,
								const float3	v,
								const float3	n,
								const float4	att)
{
		const float3 	h = normalize(v + l);
		const float		n_v = dot(n, v);
		const float		n_l = dot(n, l);
		const float		n_h = dot(n, h);
		const float		f = schlick_fresnel(h, att.y, v);
		const float		d = tr_ggx(att.x * att.x * att.x, n_l);
		const float		g = geometrical_shadowing(n_h, n_v, n_l, dot(v, h), dot(l, h));
		const float		rs = (f * d * g) / (float)(PI * n_l * n_v);

		return ((0.1 + (1.0 - 0.1) * rs));
}

__inline float	on_diffuse(	const float3	l,
							const float3	v,
							const float3	n,
							const float4	att)
{
		const float		sigma_p = 1 - att.x;
		const float		s = dot(l, v) - dot(n, l) * dot(n, v);
		const float		t = (s >= 0.0) ? max(dot(n, l), dot(n, v)) : 1.0;
		const float		a = 1 / (float)(PI + SCOEF * sigma_p);
		const float		b = sigma_p / (float)(PI + SCOEF * sigma_p);
		const float		on = att.y * dot(n, l) * (a + b * (s / (float)t));

		return (on);
}

__inline float	brdf(	const t_brdf		b)
{
	t_ray					lr = {	.dir = b.l,
									.o = b.p,
									.t = MAX_DEPTH};

	lr.o += lr.dir * 0.09f;
	check_hit(&lr, b.d);
	if (dot(b.l, b.n) > 0.0 && lr.t > b.light_dist)
	{
		float 		on = on_diffuse(b.l, b.v, b.n, b.att);
		float		ggx = ggx_specular(b.l, b.light_pos - b.p, b.v, b.n, b.att);
		return (on * ggx);
	}
	return (0.0);
}

__inline float3	lighting(	const t_ray		r,
							t_data			d)
{
	const int 	total_lights = d.light_t[0];
	t_brdf		b = {};
	float3		color = {};
	int			id;

	b.n = r.normal;
	b.p = r.o + r.dir * r.t;
	b.v = normalize(r.o - b.p);
	b.att = r.att;
	b.d = d;
	b.id = r.id;
	for (int i = 0; i < total_lights; i++){
		id = d.light_t[i * 2 + 1];
		b.light_pos = (float3)(d.light[id + 4], d.light[id + 5], d.light[id + 6]);
		b.l = normalize(b.light_pos - b.p);
		b.light_color = (float3)(d.light[id], d.light[id + 1], d.light[id + 2]);
		b.light_pow = d.light[id + 3];
		b.light_dist = length(b.light_pos - b.p);
		float		fallof = b.light_pow / (float)b.light_dist;
		color += b.light_color * b.light_pow * fallof *  brdf(b);
	}
	return (color);
}

__inline uint	color_conv(	const float3	input)
{
	uint	color = 0;

	input.r = clamp((float)input.r, 0.0f, 1.0f);
	input.g = clamp((float)input.g, 0.0f, 1.0f);
	input.b = clamp((float)input.b, 0.0f, 1.0f);

	color = 255;
	color = (color << 8) + input.r * 255.0;
	color = (color << 8) + input.g * 255.0;
	color = (color << 8) + input.b * 255.0;
	return (color);
}

__inline float3	get_skybox_pixel(	__global uint		*skybox,
									int					gid,
									float3				ray_dir,
									int2				res)
{
	float3				output;
	uint				color;
	const float2		pt = (float2){fabs(ray_dir.x), fabs(ray_dir.z)};
	uint2				cord;
	const float			angle = atan2(pt.x, pt.y);
	const float			len = (pt.y / cos(angle));
	const float3		side = {dot((float3)(1, 0, 0), ray_dir),
								dot((float3)(0, 1, 0), ray_dir),
								dot((float3)(0, 0, 1), ray_dir)};

	res.x = 2880; //skybox width
	res.y = 1440; //skybox height
	if (side.x > EPS && side.y > EPS && side.z > EPS) // +X +Y +Z :: 1
		cord = (uint2){res.x / 4, 0};
	if (side.x > EPS && side.y > EPS && side.z < EPS) // +X +Y -Z :: 2
		cord = (uint2){res.x / 2, 0};
	if (side.x > EPS && side.y < EPS && side.z > EPS) // +X -Y +Z :: 5
		cord = (uint2){res.x / 4, res.y / 2};
	if (side.x > EPS && side.y < EPS && side.z < EPS) // +X -Y -Z :: 6
		cord = (uint2){res.x / 2, res.y / 2};
	if (side.x < EPS && side.y > EPS && side.z > EPS) // -X +Y +Z :: 0
		cord = (uint2){0, 0};
	if (side.x < EPS && side.y > EPS && side.z < EPS) // -X +Y -Z :: 3
		cord = (uint2){res.x - (res.x / 4), 0};
	if (side.x < EPS && side.y < EPS && side.z > EPS) // -X -Y +Z :: 4
		cord = (uint2){0, res.y / 2};
	if (side.x < EPS && side.y < EPS && side.z < EPS) // -X -Y -Z :: 7
		cord = (uint2){res.x - (res.x / 4), res.y / 2};

	if (((side.x < EPS && side.z > EPS) || (side.x > EPS && side.z < EPS)) && side.y > EPS)
		cord.x += (1 - (angle * RAD_UNIT)) * (res.x / 4);
	else
		cord.x += (angle * RAD_UNIT) * (res.x / 4);

	if (side.y > EPS) // TESTING
		cord.y += (res.y / 2) - (sqrt(1 - powf(len, 2.0f)) * (res.y / 2)); // TESTING GOOD !!!!
	else
		cord.y += sqrt(1 - pow(len, 2)) * (res.y / 2); // TESTING

	color = skybox[(cord.y * res.x) + cord.x];

	output.b = ((color << 24) >> 24) / 255.0;
	output.g = ((color << 16) >> 24) / 255.0;
	output.r = ((color << 8) >> 24) / 255.0;
	return (output);
}

__inline float3	metallic(	t_ray			r,
							t_data			d)
{
	float3			final_col = {};
	float3			coef = r.att.y;
	t_ray 			ref = {.dir = reflect(r.dir, r.normal), .o = r.o + r.dir * r.t,
							.t = MAX_DEPTH};

 	for (int i = 0; i < 4; i++){
		ref.o += ref.dir * 0.09f;
		check_hit(&ref, d);
		if (ref.t < MAX_DEPTH){
			final_col += lighting(ref, d) * coef;
			if (ref.att.w != 1){
				final_col = ref.color + lighting(ref, d) * coef;
				break;
			}
		}
		else {
			if (d.skbx_enable == 1)
				final_col += get_skybox_pixel(d.skybox, d.gid, ref.dir, d.res);
			else
				final_col += (float3)(0.01, 0.01, 0.01);
			break;
		}
		ref.o = ref.o + ref.dir * ref.t;
		ref.dir = reflect(ref.dir, ref.normal);
		ref.t = MAX_DEPTH;
		coef *= ref.att.y;
	}
	return (final_col * coef);
}

__inline float3 color_filter( 	const float3 		c,
								int					filter)
{
	float3						color;

	if (filter == SEPIA)
	{
		color.x = c.x * 0.393f + c.y * 0.769f + c.z * 0.189f;
		color.y = c.x * 0.349f + c.y * 0.686f + c.z * 0.168f;
		color.z = c.x * 0.272f + c.y * 0.534f + c.z * 0.131f;
	}
	else if (filter == GRAYSCALE)
	{
		color.x = (c.x + c.y + c.z) / (float)3.0f;
		color.y = (c.x + c.y + c.z) / (float)3.0f;
		color.z = (c.x + c.y + c.z) / (float)3.0f;
	}
	else if (filter == CELSHADE)
	{
		color.x = floor(c.x * 3.0f) / (float)3.0f;
		color.y = floor(c.y * 3.0f) / (float)3.0f;
		color.z = floor(c.z * 3.0f) / (float)3.0f;
	}
	else
		color = c;
	return (color);
}


__kernel void	render(	__global float					*info,
						__global uint					*image,
						__global float					*obj,
						__global int					*obj_table,
						__global float					*light,
						__global int					*light_table,
						__global uint					*skybox)
{
	const t_cam			cam = {	.pos = {info[0], info[1], info[2]},
								.w = {info[3], info[4], info[5]},
								.u = {info[6], info[7], info[8]},
								.v = {info[9], info[10], info[11]}};
	const int2			res = {(int)info[12], (int)info[13]};
	const int2			skbx_size = {(int)info[16], (int)info[17]};
	const int			filter = (int)info[14];
	const int			gid = get_global_id(0);
	const t_data		d = {	.obj = obj, .obj_t = obj_table,
								.light = light, .light_t = light_table,
								.res = res, .skybox = skybox, .gid = gid,
								.skbx_enable = (int)info[15]};
	const int2			pix = {gid % res.x, gid / res.x};
	t_ray				r = {.o = cam.pos,
							.dir = normalize(pix.x * cam.u + pix.y * (-cam.v) + cam.w),
							.t = MAX_DEPTH, .id = 0};

	check_hit(&r, d);
	if (r.t < MAX_DEPTH) {
		if (r.att.w == 1)
			r.color = metallic(r, d);
		else {
			r.color += lighting(r, d) * (r.att.y);
			if (r.att.x <= 0.2){
				r.color *= metallic(r, d) * (r.att.y + (0.2f - r.att.x * 0.2f));
			}
		}
	}
	else if (d.skbx_enable == 1)
		r.color = get_skybox_pixel(skybox, gid, r.dir, skbx_size);
	if (filter > 0)
		r.color = color_filter(r.color, filter);
	barrier(CLK_GLOBAL_MEM_FENCE);
	image[gid] = color_conv(r.color);
}
