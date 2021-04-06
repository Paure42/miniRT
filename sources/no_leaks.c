/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:55:48 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:55:50 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void	free_objects2(t_mrt *mrt)
{
	while (mrt->pl)
	{
		mrt->cur_pl = mrt->pl;
		mrt->pl = mrt->pl->next;
		free(mrt->cur_pl);
		mrt->cur_pl = NULL;
	}
	while (mrt->cy)
	{
		mrt->cur_cy = mrt->cy;
		mrt->cy = mrt->cy->next;
		free(mrt->cur_cy);
		mrt->cur_cy = NULL;
	}
	while (mrt->di)
	{
		mrt->cur_di = mrt->di;
		mrt->di = mrt->di->next;
		free(mrt->cur_di);
		mrt->cur_di = NULL;
	}
}

static void	free_objects(t_mrt *mrt)
{
	while (mrt->sp)
	{
		mrt->cur_sp = mrt->sp;
		mrt->sp = mrt->sp->next;
		free(mrt->cur_sp);
		mrt->cur_sp = NULL;
	}
	while (mrt->tr)
	{
		mrt->cur_tr = mrt->tr;
		mrt->tr = mrt->tr->next;
		free(mrt->cur_tr);
		mrt->cur_tr = NULL;
	}
	while (mrt->sq)
	{
		mrt->cur_sq = mrt->sq;
		mrt->sq = mrt->sq->next;
		free(mrt->cur_sq);
		mrt->cur_sq = NULL;
	}
	free_objects2(mrt);
}

void		no_leaks(t_mrt *mrt)
{
	if (mrt->mlx_ptr && mrt->win_ptr)
		mlx_destroy_window(mrt->mlx_ptr, mrt->win_ptr);
	free_objects(mrt);
}
