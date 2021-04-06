/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:13:02 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:13:02 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void		end_parsing_triangle(t_mrt *mrt)
{
	if (mrt->cur_tr->mat.reflect == -1)
		mrt->cur_tr->mat.reflect = 0.0f;
	mrt->cur_tr->mat.rgb.r /= 255.0f;
	mrt->cur_tr->mat.rgb.g /= 255.0f;
	mrt->cur_tr->mat.rgb.b /= 255.0f;
	mrt->cur_tr->save.a = mrt->cur_tr->mat.rgb.r;
	mrt->cur_tr->save.b = mrt->cur_tr->mat.rgb.g;
	mrt->cur_tr->save.c = mrt->cur_tr->mat.rgb.b;
	mrt->cur_tr->pos1 = mrt->cur_tr->save.pos1;
	mrt->cur_tr->pos2 = mrt->cur_tr->save.pos2;
	mrt->cur_tr->pos3 = mrt->cur_tr->save.pos3;
}

static void		check_error_triangle(t_mrt *mrt)
{
	check_vector_error_inf(mrt, mrt->cur_tr->save.pos1,
			mrt->cur_tr->save.pos2, mrt->cur_tr->save.pos3);
	check_color_error(mrt, mrt->cur_tr->mat.rgb);
	if (mrt->error == 1)
		ft_putstr_fd("Error parsing triangle\n", 1);
}

static void		init_triangle(t_mrt *mrt)
{
	if (!mrt->tr)
	{
		mrt->tr = tr_lstnew();
		mrt->cur_tr = mrt->tr;
	}
	else
	{
		tr_lstadd_back(&mrt->tr, tr_lstnew());
		mrt->cur_tr = mrt->cur_tr->next;
	}
	vector_init_inf(&mrt->cur_tr->save.pos1);
	vector_init_inf(&mrt->cur_tr->save.pos2);
	vector_init_inf(&mrt->cur_tr->save.pos3);
	color_init(&mrt->cur_tr->mat.rgb);
	mrt->cur_tr->mat.reflect = -1;
}

static void		parsing_triangle2(t_mrt *mrt, char *str, int i)
{
	if (mrt->cur_tr->save.pos1.z == 1.0 / 0.0)
		mrt->cur_tr->save.pos1.z = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos2.x == 1.0 / 0.0)
		mrt->cur_tr->save.pos2.x = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos2.y == 1.0 / 0.0)
		mrt->cur_tr->save.pos2.y = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos2.z == 1.0 / 0.0)
		mrt->cur_tr->save.pos2.z = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos3.x == 1.0 / 0.0)
		mrt->cur_tr->save.pos3.x = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos3.y == 1.0 / 0.0)
		mrt->cur_tr->save.pos3.y = ft_atof(str + i);
	else if (mrt->cur_tr->save.pos3.z == 1.0 / 0.0)
		mrt->cur_tr->save.pos3.z = ft_atof(str + i);
	else if (mrt->cur_tr->mat.rgb.r == -1)
		mrt->cur_tr->mat.rgb.r = ft_atof(str + i);
	else if (mrt->cur_tr->mat.rgb.g == -1)
		mrt->cur_tr->mat.rgb.g = ft_atof(str + i);
	else if (mrt->cur_tr->mat.rgb.b == -1)
		mrt->cur_tr->mat.rgb.b = ft_atof(str + i);
}

void			parsing_triangle(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	init_triangle(mrt);
	while (str[i])
	{
		if (((str[i] >= '0' && str[i] <= '9') || str[i] == 'r' ||
			str[i] == '-') && i > 2)
		{
			if (str[i] == 'r' && mrt->cur_tr->mat.reflect == -1)
				mrt->cur_tr->mat.reflect = ft_atof(str + i);
			else if (mrt->cur_tr->save.pos1.x == 1.0 / 0.0)
				mrt->cur_tr->save.pos1.x = ft_atof(str + i);
			else if (mrt->cur_tr->save.pos1.y == 1.0 / 0.0)
				mrt->cur_tr->save.pos1.y = ft_atof(str + i);
			else
				parsing_triangle2(mrt, str, i);
			while (str[i] && (str[i] != ' ' && str[i] != ',' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_triangle(mrt);
	end_parsing_triangle(mrt);
}
