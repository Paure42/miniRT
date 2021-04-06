/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:55:10 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:55:11 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void		init_inner_loop(t_mrt *mrt, int *level, int x, int y)
{
	*level = -1;
	mrt->new_start.z = -1;
	mrt->new_start.x = (2 * (x + 0.5) / mrt->rx - 1) *
	mrt->win_ratio * mrt->win_scale;
	mrt->new_start.y = (1 - 2 * (y + 0.5) / mrt->ry) * mrt->win_scale;
	compute_camera(mrt, mrt->new_start.x, mrt->new_start.y);
	mrt->new_start.x += mrt->cur_cam->pos.x;
	mrt->new_start.y += mrt->cur_cam->pos.y;
	mrt->new_start.z = mrt->cur_cam->pos.z;
	mrt->tmpr = mrt->argb.r;
	mrt->tmpg = mrt->argb.g;
	mrt->tmpb = mrt->argb.b;
	mrt->rcoef = 1.0f;
}

static int		img_to_window(t_mrt *mrt)
{
	mlx_put_image_to_window(mrt->mlx_ptr, mrt->win_ptr, mrt->img_ptr, 0, 0);
	return (1);
}

static int		raytracer_end(t_mrt *mrt, int x, int y)
{
	if (mrt->save == 1)
	{
		bmp_save(mrt, x, y);
		mlx_destroy_image(mrt->mlx_ptr, mrt->img_ptr);
		exit_prog(mrt);
	}
	else
	{
		img_to_window(mrt);
		mlx_hook(mrt->win_ptr, 17, 1L << 17, exit_prog, mrt);
		mlx_hook(mrt->win_ptr, 15, 1L << 16, img_to_window, mrt);
		mlx_key_hook(mrt->win_ptr, handle_key, mrt);
		mlx_mouse_hook(mrt->win_ptr, handle_mouse, mrt);
		mlx_loop(mrt->mlx_ptr);
		mrt->first_call = 0;
	}
	return (1);
}

static void		call_objects(t_mrt *mrt, double *t, int level)
{
	*t = 1.0 / 0.0;
	mrt->ret = NULL;
	mrt->r.start = mrt->new_start;
	mrt->r.dir = mrt->new_dir;
	if (mrt->sp != NULL)
		raytracer_sp(mrt, &mrt->r, t, level);
	if (mrt->pl != NULL)
		raytracer_pl(mrt, &mrt->r, t);
	if (mrt->tr != NULL)
		raytracer_tr(mrt, &mrt->r, t);
	if (mrt->sq != NULL)
		raytracer_sq(mrt, &mrt->r, t);
	if (mrt->cy != NULL)
		raytracer_cy(mrt, &mrt->r, t);
	if (mrt->di != NULL)
		raytracer_di(mrt, &mrt->r, t);
	if (mrt->ret == NULL)
		return ;
	check_light(mrt->ret, mrt->n, mrt, t);
}

int				raytracing_hub(t_mrt *mrt)
{
	int			x;
	int			y;
	double		t;
	int			level;

	compute_all(mrt);
	y = -1;
	while (++y < mrt->ry)
	{
		x = -1;
		while (++x < mrt->rx)
		{
			init_inner_loop(mrt, &level, x, y);
			while (++level < 15 && mrt->rcoef > 0.0f)
			{
				call_objects(mrt, &t, level);
				if (mrt->ret == NULL)
					break ;
			}
			*(int*)(mrt->img_data + (x * 4 + (mrt->img_size * y))) =
			rgb_manage(mrt->tmpr, mrt->tmpg, mrt->tmpb);
		}
	}
	raytracer_end(mrt, x, y);
	return (1);
}
