/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_disk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:43:18 by paure             #+#    #+#             */
/*   Updated: 2020/05/14 18:43:21 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void		init_disk(t_mrt *mrt)
{
	if (mrt->di == NULL)
	{
		mrt->di = di_lstnew();
		mrt->cur_di = mrt->di;
	}
	else
	{
		di_lstadd_back(&mrt->di, di_lstnew());
		mrt->cur_di = mrt->cur_di->next;
	}
	vector_init_inf(&mrt->cur_di->pos);
	vector_init_inf(&mrt->cur_di->ori);
	color_init(&mrt->cur_di->mat.rgb);
	mrt->cur_di->mat.reflect = -1;
	mrt->cur_di->radius = -1;
}

static void		check_error_disk(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_di->pos,
		mrt->cur_di->ori, mrt->cur_di->pos);
	check_color_error(mrt, mrt->cur_di->mat.rgb);
	if (mrt->cur_di->radius < 0 || mrt->error == 1)
	{
		mrt->error = 1;
		ft_putstr_fd("Error parsing disk\n", 1);
	}
}

static void		end_parsing_disk(t_mrt *mrt)
{
	if (mrt->cur_di->mat.reflect == -1)
		mrt->cur_di->mat.reflect = 0;
	mrt->cur_di->mat.rgb.r /= 255.0f;
	mrt->cur_di->mat.rgb.g /= 255.0f;
	mrt->cur_di->mat.rgb.b /= 255.0f;
	mrt->cur_di->n = vector_normalize(mrt->cur_di->ori);
	mrt->cur_di->radius /= 2;
}

static void		parsing_disk2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_di->pos.z == 1.0 / 0.0)
		mrt->cur_di->pos.z = ft_atof(str + i);
	else if (mrt->cur_di->ori.x == 1.0 / 0.0)
		mrt->cur_di->ori.x = ft_atof(str + i);
	else if (mrt->cur_di->ori.y == 1.0 / 0.0)
		mrt->cur_di->ori.y = ft_atof(str + i);
	else if (mrt->cur_di->ori.z == 1.0 / 0.0)
		mrt->cur_di->ori.z = ft_atof(str + i);
	else if (mrt->cur_di->radius == -1)
		mrt->cur_di->radius = ft_atof(str + i);
	else if (mrt->cur_di->mat.rgb.r == -1)
		mrt->cur_di->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_di->mat.rgb.g == -1)
		mrt->cur_di->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_di->mat.rgb.b == -1)
		mrt->cur_di->mat.rgb.b = ft_atof(str + i);
}

void			parsing_disk(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_disk(mrt);
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' || str[i] == '-')
		{
			if (str[i] == 'r' && mrt->cur_di->mat.reflect == -1)
				mrt->cur_di->mat.reflect = ft_atof(str + i);
			else if (mrt->cur_di->pos.x == 1.0 / 0.0)
				mrt->cur_di->pos.x = ft_atof(str + i);
			else if (mrt->cur_di->pos.y == 1.0 / 0.0)
				mrt->cur_di->pos.y = ft_atof(str + i);
			else
				parsing_disk2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_disk(mrt);
	end_parsing_disk(mrt);
}
