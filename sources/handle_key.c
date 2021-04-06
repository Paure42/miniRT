/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:54:56 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:54:57 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static	int			handle_key2(int key_code, t_mrt *mrt)
{
	if (key_code == 97)
	{
		if (mrt->cur_cam->next)
			mrt->cur_cam = mrt->cur_cam->next;
		raytracing_hub(mrt);
	}
	else if (key_code == 122)
	{
		mrt->cur_cam = mrt->cam;
		raytracing_hub(mrt);
	}
	return (1);
}

int					handle_key(int key_code, t_mrt *mrt)
{
	if (key_code == 65307)
		exit_prog(mrt);
	else if (key_code == 65363)
	{
		mrt->cur_cam->pos.x += mrt->cur_cam->fov / 5;
		raytracing_hub(mrt);
	}
	else if (key_code == 65361)
	{
		mrt->cur_cam->pos.x -= mrt->cur_cam->fov / 5;
		raytracing_hub(mrt);
	}
	else if (key_code == 65362)
	{
		mrt->cur_cam->pos.y += mrt->cur_cam->fov / 5;
		raytracing_hub(mrt);
	}
	else if (key_code == 65364)
	{
		mrt->cur_cam->pos.y -= mrt->cur_cam->fov / 5;
		raytracing_hub(mrt);
	}
	return (handle_key2(key_code, mrt));
}

int					handle_mouse(int key_code, int x, int y, t_mrt *mrt)
{
	x = y;
	y = x;
	if (key_code == 4)
	{
		mrt->cur_cam->pos.z -= 5;
		raytracing_hub(mrt);
	}
	else if (key_code == 5)
	{
		mrt->cur_cam->pos.z += 5;
		raytracing_hub(mrt);
	}
	return (1);
}

int					exit_prog(t_mrt *mrt)
{
	no_leaks(mrt);
	exit(1);
	return (1);
}
