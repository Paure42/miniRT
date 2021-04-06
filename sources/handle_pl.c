/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:49:37 by paure             #+#    #+#             */
/*   Updated: 2020/06/03 15:49:38 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static bool		intersect_plane(t_plane *ret, t_ray *r, double *t)
{
	double		denom;
	double		a;
	double		b;
	double		dist;

	denom = -vector_dot(ret->pos, ret->n);
	a = vector_dot(ret->n, r->start) + denom;
	b = vector_dot(r->dir, ret->n);
	dist = -(a / b);
	if (dist > EPSILON && dist < *t)
	{
		*t = dist;
		return (true);
	}
	return (false);
}

bool			raytracer_pl(t_mrt *mrt, t_ray *r, double *t)
{
	t_plane	*ret;

	mrt->cur_pl = mrt->pl;
	ret = NULL;
	while (mrt->cur_pl)
	{
		mrt->cur_pl->r.start = r->start;
		mrt->cur_pl->r.dir = r->dir;
		if ((intersect_plane(mrt->cur_pl, &mrt->cur_pl->r, t)) == true)
			ret = mrt->cur_pl;
		mrt->cur_pl = mrt->cur_pl->next;
	}
	if (ret != NULL)
	{
		mrt->new_start = vector_add(ret->r.start, vector_scale(*t, ret->r.dir));
		mrt->n = vector_normalize(ret->n);
		mrt->ret = &ret->mat;
		return (true);
	}
	return (false);
}
