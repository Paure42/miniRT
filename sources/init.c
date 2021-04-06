/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:55:41 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:55:42 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	vector_init(t_vector *v1)
{
	v1->x = -1;
	v1->y = -1;
	v1->z = -1;
}

void	color_init(t_color *rgb)
{
	rgb->r = -1;
	rgb->g = -1;
	rgb->b = -1;
}

void	vector_init_inf(t_vector *v1)
{
	v1->x = 1.0 / 0.0;
	v1->y = 1.0 / 0.0;
	v1->z = 1.0 / 0.0;
}

void	compute_all(t_mrt *mrt)
{
	if (mrt->tr != NULL)
		compute_tr(mrt);
	if (mrt->sq != NULL)
		compute_sq(mrt);
	if (mrt->img_ptr != NULL)
		mlx_destroy_image(mrt->mlx_ptr, mrt->img_ptr);
	mrt->img_ptr = mlx_new_image(mrt->mlx_ptr, mrt->rx, mrt->ry);
	mrt->img_data = mlx_get_data_addr(mrt->img_ptr, &mrt->bpp,
		&mrt->img_size, &mrt->endian);
	mrt->win_scale = tan(deg2rad(mrt->cur_cam->fov * 0.5));
}
