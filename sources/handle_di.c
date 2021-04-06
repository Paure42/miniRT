/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_di.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:49:10 by paure             #+#    #+#             */
/*   Updated: 2020/06/03 15:49:12 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static bool	intersect_disk(t_disk *ret, t_ray *r, double *t)
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
		denom = vector_dot(vector_sub(ret->n, ret->pos),
			vector_add(r->start, vector_scale(dist, r->dir)));
		if (denom <= (ret->radius * ret->radius))
		{
			*t = dist;
			return (true);
		}
	}
	return (false);
}

bool		raytracer_di(t_mrt *mrt, t_ray *r, double *t)
{
	t_disk	*ret;

	mrt->cur_di = mrt->di;
	ret = NULL;
	while (mrt->cur_di)
	{
		mrt->cur_di->r.start = r->start;
		mrt->cur_di->r.dir = r->dir;
		if ((intersect_disk(mrt->cur_di, &mrt->cur_di->r, t)) == true)
			ret = mrt->cur_di;
		mrt->cur_di = mrt->cur_di->next;
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
