/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:56:26 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:56:27 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <stdbool.h>
# define EPSILON 0.0000001f

typedef struct			s_vector
{
	double	x;
	double	y;
	double	z;
}						t_vector;

typedef struct			s_color
{
	double	r;
	double	g;
	double	b;
	char	*rgb;
}						t_color;

typedef struct			s_save_data
{
	double		a;
	double		b;
	double		c;
	double		radius;
	double		distance;
	t_vector	pos1;
	t_vector	pos2;
	t_vector	pos3;
}						t_save;

typedef struct			s_light
{
	t_vector		pos;
	double			intensity;
	t_color			color;
	t_save			save;
	struct s_light	*next;
}						t_light;

typedef struct			s_ray
{
	t_vector	start;
	t_vector	dir;
}						t_ray;

typedef struct			s_material
{
	t_color	rgb;
	double	coef;
	double	reflect;
}						t_mat;

typedef struct			s_sphere
{
	t_vector		pos;
	t_mat			mat;
	t_ray			r;
	double			radius;
	t_save			save;
	struct s_sphere *next;
}						t_sphere;

typedef struct			s_cylinder
{
	t_vector			pos;
	t_vector			ori;
	short int			cap;
	double				radius;
	double				h;
	double				t;
	double				t0;
	double				t1;
	double				dist;
	t_vector			n1;
	t_vector			hit1;
	t_vector			hit2;
	t_vector			hit3;
	t_vector			top;
	t_vector			bot;
	t_vector			i;
	t_vector			o;
	t_mat				mat;
	t_vector			n;
	t_ray				r;
	struct s_cylinder	*next;
}						t_cylinder;

typedef struct			s_disk
{
	t_vector			pos;
	t_vector			ori;
	double				radius;
	t_mat				mat;
	t_vector			n;
	t_ray				r;
	struct s_disk		*next;
}						t_disk;

typedef struct			s_square
{
	t_vector		pos;
	t_vector		ori;
	double			h;
	t_mat			mat;
	t_save			save;
	t_vector		e1;
	t_vector		e2;
	t_vector		proj1;
	t_vector		proj2;
	t_vector		inter;
	t_vector		v;
	t_ray			r;
	t_vector		n;
	struct s_square	*next;
}						t_square;

typedef	struct			s_triangle
{
	t_vector			pos1;
	t_vector			pos2;
	t_vector			pos3;
	t_ray				r;
	t_mat				mat;
	t_save				save;
	t_vector			normal;
	t_vector			pvec;
	t_vector			v0v1;
	t_vector			v0v2;
	t_vector			v1v2;
	t_vector			z1;
	t_vector			z2;
	t_vector			z3;
	double				u;
	double				v;
	struct s_triangle	*next;
}						t_triangle;

typedef struct			s_plane
{
	t_vector		pos;
	t_vector		ori;
	t_mat			mat;
	t_ray			r;
	t_save			save;
	t_vector		n;
	struct s_plane	*next;
}						t_plane;

typedef struct			s_camera
{
	t_vector		pos;
	t_vector		dir;
	double			fov;
	struct s_camera	*next;
}						t_cam;

typedef struct			s_bmp
{
	char		file_type[2];
	int			file_size;
	int			reserved;
	int			offset;
	int			header_size;
	int			img_width;
	int			img_height;
	int			planes;
	int			bpp;
	int			compression;
	int			img_size;
	int			x_pixels;
	int			y_pixels;
	int			total_colors;
	int			important_colors;

}						t_bmp;

typedef struct			s_mini_rt
{
	double		ali;
	double		rcoef;
	double		reflect;
	double		rx;
	double		ry;
	double		tmpb;
	double		tmpg;
	double		tmpr;
	double		win_scale;
	double		win_ratio;
	int			first_call;
	int			save;
	int			bpp;
	int			endian;
	int			error;
	int			pos;
	int			img_size;
	char		*img_data;
	void		*img_ptr;
	void		*mlx_ptr;
	void		*win_ptr;
	t_cylinder	*cur_cy;
	t_cylinder	*cy;
	t_triangle	*cur_tr;
	t_triangle	*tr;
	t_sphere	*cur_sp;
	t_sphere	*sp;
	t_square	*cur_sq;
	t_square	*sq;
	t_plane		*cur_pl;
	t_plane		*pl;
	t_disk		*cur_di;
	t_disk		*di;
	t_color		argb;
	t_light		*cur_li;
	t_light		*li;
	t_cam		*cam;
	t_cam		*cur_cam;
	t_vector	dist;
	t_vector	n;
	t_vector	new_dir;
	t_vector	new_start;
	t_vector	scaled;
	t_ray		r;
	t_mat		*ret;
}						t_mrt;
int						main(int argc, char **argv);
void					check_light(t_mat *ret, t_vector n,
							t_mrt *mrt, double *t);
void					bmp_save(t_mrt *mrt, int x, int y);
double					calc_dist_fabs(t_vector v1, t_vector v2);
double					calc_dist(t_vector v1, t_vector v2);
t_vector				calc_v_dir(t_vector	rdir);
t_vector				calc_w_dir(t_vector rdir, t_vector u);
void					cam_lstadd_front(t_cam **alst, t_cam *new);
void					cam_lstadd_back(t_cam **alst, t_cam *new);
t_cam					*cam_lstlast(t_cam *lst);
t_cam					*cam_lstnew(void);
int						cam_lstsize(t_cam *lst);
void					check_vector_error(t_mrt *mrt, t_vector v1,
							t_vector v2, t_vector v3);
void					check_vector_error_inf(t_mrt *mrt,
							t_vector v1, t_vector v2, t_vector v3);
void					check_color_error(t_mrt *mrt, t_color col);
void					color_init(t_color *rgb);
void					compute_all(t_mrt *mrt);
void					compute_camera(t_mrt *mrt, double x, double y);
void					compute_tr(t_mrt *mrt);
void					compute_pl(t_mrt *mrt);
void					compute_sq(t_mrt *mrt);
unsigned int			create_rgb(int r, int g, int b);
void					create_window(t_mrt *mrt);
void					cy_lstadd_front(t_cylinder **alst, t_cylinder *new);
void					cy_lstadd_back(t_cylinder **alst, t_cylinder *new);
t_cylinder				*cy_lstlast(t_cylinder *lst);
t_cylinder				*cy_lstnew(void);
int						cy_lstsize(t_cylinder *lst);
double					deg2rad(double deg);
void					di_lstadd_front(t_disk **alst, t_disk *new);
void					di_lstadd_back(t_disk **alst, t_disk *new);
t_disk					*di_lstlast(t_disk *lst);
t_disk					*di_lstnew(void);
int						di_lstsize(t_disk *lst);
int						exit_prog(t_mrt *mrt);
bool					find_closest_sp(float discr, double c,
							double b, double *t);
int						handle_key(int key_code, t_mrt *mrt);
int						handle_mouse(int key_code, int x, int y, t_mrt *mrt);
int						init_window(int fd, t_mrt *mrt);
void					li_lstadd_front(t_light **alst, t_light *new);
void					li_lstadd_back(t_light **alst, t_light *new);
t_light					*li_lstlast(t_light *lst);
t_light					*li_lstnew(void);
unsigned int			min(double a, double b);
void					mult_vec_matrix(t_vector *src,
							t_vector *dst, double x[4][4]);
void					mult_dir_matrix(t_vector *src,
							t_vector *dst, double x[4][4]);
void					no_leaks(t_mrt *mrt);
t_vector				new_vec3(double x, double y, double z);
int						li_lstsize(t_light *lst);
void					pl_lstadd_front(t_plane **alst, t_plane *new);
void					pl_lstadd_back(t_plane **alst, t_plane *new);
t_plane					*pl_lstlast(t_plane *lst);
t_plane					*pl_lstnew(void);
int						pl_lstsize(t_plane *lst);
void					parsing_hub(t_mrt *mrt, char *str);
void					parsing_resolution(t_mrt *mrt, char *str);
void					parsing_ambient_light(t_mrt *mrt, char *str);
void					parsing_camera(t_mrt *mrt, char *str);
void					parsing_cylinder(t_mrt *mrt, char *str);
void					parsing_disk(t_mrt *mrt, char *str);
void					parsing_light(t_mrt *mrt, char *str);
void					parsing_sphere(t_mrt *mrt, char *str);
void					parsing_triangle(t_mrt *mrt, char *str);
void					parsing_square(t_mrt *mrt, char *str);
void					parsing_plane(t_mrt *mrt, char *str);
bool					raytracer_sp(t_mrt *mrt, t_ray *r,
							double *t, int level);
bool					raytracer_cy(t_mrt *mrt, t_ray *r, double *t);
bool					raytracer_tr(t_mrt *mrt, t_ray *r, double *t);
bool					raytracer_sq(t_mrt *mrt, t_ray *r, double *t);
bool					raytracer_pl(t_mrt *mrt, t_ray *r, double *t);
bool					raytracer_di(t_mrt *mrt, t_ray *r, double *t);
int						reading_file(t_mrt *mrt, int fd);
int						raytracing_hub(t_mrt *mrt);
unsigned int			rgb_hex(int rgb[4]);
int						rgb_manage(double r, double g, double b);
void					sp_lstadd_back(t_sphere **alst, t_sphere *new);
void					sp_lstadd_front(t_sphere **alst, t_sphere *new);
t_sphere				*sp_lstlast(t_sphere *lst);
t_sphere				*sp_lstnew(void);
int						sp_lstsize(t_sphere *lst);
void					sq_lstadd_front(t_square **alst, t_square *new);
void					sq_lstadd_back(t_square **alst, t_square *new);
t_square				*sq_lstlast(t_square *lst);
t_square				*sq_lstnew(void);
int						sq_lstsize(t_square *lst);
void					tr_lstadd_front(t_triangle **alst, t_triangle *new);
void					tr_lstadd_back(t_triangle **alst, t_triangle *new);
t_triangle				*tr_lstlast(t_triangle *lst);
t_triangle				*tr_lstnew(void);
int						tr_lstsize(t_triangle *lst);
t_vector				vector_add(t_vector v1, t_vector v2);
t_vector				vector_cross(t_vector v1, t_vector v2);
t_vector				vector_divide(t_vector v1, t_vector v2);
void					vector_init(t_vector *v1);
void					vector_init_inf(t_vector *v1);
t_vector				vector_add(t_vector v1, t_vector v2);
double					vector_dot(t_vector v1, t_vector v2);
t_vector				vector_normalize(t_vector v1);
t_vector				vector_scale(double c, t_vector v);
double					vector_squared(t_vector v1);
t_vector				vector_sub(t_vector v1, t_vector v2);
#endif
