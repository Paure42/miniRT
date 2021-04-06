/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_square.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:45:07 by paure             #+#    #+#             */
/*   Updated: 2020/05/14 18:45:09 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void		init_square(t_mrt *mrt)
{
	if (!mrt->sq)
	{
		mrt->sq = sq_lstnew();
		mrt->cur_sq = mrt->sq;
	}
	else
	{
		sq_lstadd_back(&mrt->sq, sq_lstnew());
		mrt->cur_sq = mrt->cur_sq->next;
	}
	vector_init_inf(&mrt->cur_sq->pos);
	vector_init_inf(&mrt->cur_sq->ori);
	color_init(&mrt->cur_sq->mat.rgb);
	mrt->cur_sq->mat.reflect = -1;
	mrt->cur_sq->h = -1;
}

static void		check_error_square(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_sq->pos,
			mrt->cur_sq->ori, mrt->cur_sq->pos);
	check_color_error(mrt, mrt->cur_sq->mat.rgb);
	if (mrt->cur_sq->ori.x > 1.0f || mrt->cur_sq->ori.x < -1.0f
		|| mrt->cur_sq->ori.y > 1.0f || mrt->cur_sq->ori.y < -1.0f
		|| mrt->cur_sq->ori.z > 1.0f || mrt->cur_sq->ori.z < -1.0f
		|| mrt->error == 1 || mrt->cur_sq->h < 0)
	{
		mrt->error = 1;
		ft_putstr_fd("Error parsing square\n", 1);
	}
}

static void		end_parsing_square(t_mrt *mrt)
{
	if (mrt->cur_sq->mat.reflect == -1)
		mrt->cur_sq->mat.reflect = 0;
	mrt->cur_sq->mat.rgb.r /= 255.0f;
	mrt->cur_sq->mat.rgb.g /= 255.0f;
	mrt->cur_sq->mat.rgb.b /= 255.0f;
	mrt->cur_sq->save.pos1 = mrt->cur_sq->pos;
	mrt->cur_sq->n = mrt->cur_sq->ori;
}

static void		parsing_square2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_sq->pos.z == 1.0 / 0.0)
		mrt->cur_sq->pos.z = ft_atof(str + i);
	else if (mrt->cur_sq->ori.x == 1.0 / 0.0)
		mrt->cur_sq->ori.x = ft_atof(str + i);
	else if (mrt->cur_sq->ori.y == 1.0 / 0.0)
		mrt->cur_sq->ori.y = ft_atof(str + i);
	else if (mrt->cur_sq->ori.z == 1.0 / 0.0)
		mrt->cur_sq->ori.z = ft_atof(str + i);
	else if (mrt->cur_sq->h == -1)
		mrt->cur_sq->h = ft_atof(str + i);
	else if (mrt->cur_sq->mat.rgb.r == -1)
		mrt->cur_sq->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_sq->mat.rgb.g == -1)
		mrt->cur_sq->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_sq->mat.rgb.b == -1)
		mrt->cur_sq->mat.rgb.b = ft_atof(str + i);
}

void			parsing_square(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_square(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mrt->cur_sq->mat.reflect == -1)
				mrt->cur_sq->mat.reflect = ft_atof(str + i);
			else if (mrt->cur_sq->pos.x == 1.0 / 0.0)
				mrt->cur_sq->pos.x = ft_atof(str + i);
			else if (mrt->cur_sq->pos.y == 1.0 / 0.0)
				mrt->cur_sq->pos.y = ft_atof(str + i);
			else
				parsing_square2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_square(mrt);
	end_parsing_square(mrt);
}
