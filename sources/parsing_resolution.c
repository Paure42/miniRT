/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_resolution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 18:43:32 by paure             #+#    #+#             */
/*   Updated: 2020/05/14 18:43:55 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void		check_error_resolution(t_mrt *mrt)
{
	if (mrt->rx == -1 || mrt->ry == -1 || mrt->error == 1)
	{
		mrt->error = 1;
		ft_putstr_fd("Error parsing resolution\n", 1);
	}
}

static void		end_parsing_resolution(t_mrt *mrt)
{
	if (mrt->rx > 1280)
		mrt->rx = 1280;
	if (mrt->ry > 720)
		mrt->ry = 720;
	if (mrt->rx > mrt->ry)
		mrt->win_ratio = mrt->rx / mrt->ry;
	else
		mrt->win_ratio = mrt->ry / mrt->rx;
}

void			parsing_resolution(t_mrt *mrt, char *str)
{
	int	i;

	i = 0;
	if (mrt->rx != -1 || mrt->ry != -1)
		mrt->error = 1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (mrt->rx == -1)
				mrt->rx = ft_atof(str + i);
			else if (mrt->ry == -1)
				mrt->ry = ft_atof(str + i);
			else
				mrt->error = 1;
			while (str[i] && (str[i] != ' ' && str[i] != '	'))
				i++;
		}
		if (str[i])
			i++;
	}
	check_error_resolution(mrt);
	end_parsing_resolution(mrt);
}
