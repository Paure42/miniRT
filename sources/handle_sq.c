/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:49:55 by paure             #+#    #+#             */
/*   Updated: 2020/06/03 15:49:56 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void				compute_sq(t_mrt *mrt)
{
	t_vector	u;
	t_vector	v;
	t_vector	w;

	mrt->cur_sq = mrt->sq;
	while (mrt->cur_sq)
	{
		u = vector_normalize(mrt->cur_sq->n);
		v = new_vec3(0, 1, 0);
		if (u.x == 0 && (u.y == 1 || u.y == -1) && u.z == 0)
		{
			v.x = 0;
			v.y = 0.9999;
			v.z = 0.00001;
		}
		v = vector_normalize(v);
		v = vector_normalize(vector_sub(v, vector_scale(vector_dot(u, v), u)));
		w = vector_normalize(vector_cross(v, u));
		mrt->cur_sq->e1 = vector_sub(vector_add(mrt->cur_sq->pos,
			vector_scale(mrt->cur_sq->h / 2, v)), mrt->cur_sq->pos);
		mrt->cur_sq->e2 = vector_sub(vector_add(mrt->cur_sq->pos,
			vector_scale(mrt->cur_sq->h / 2, w)), mrt->cur_sq->pos);
		mrt->cur_sq = mrt->cur_sq->next;
	}
}

static bool			intersect_square(t_mrt *mrt, t_square *ret, t_ray *r,
	double *t)
{
	double		denom;
	double		dist;
	t_vector	hit;

	denom = -vector_dot(ret->pos, ret->n);
	dist = -((vector_dot(ret->n, r->start) + denom) /
		(vector_dot(r->dir, ret->n)));
	if (dist > EPSILON && dist < *t)
	{
		hit = vector_add(r->start, vector_scale(dist, r->dir));
		if (mrt->rcoef == 1.0f)
			if (!(fabs(vector_dot(vector_sub(hit, ret->pos), ret->e1)) <
				pow(ret->h / 2, 2) && fabs(vector_dot(
				vector_sub(hit, ret->pos), ret->e2)) < pow(ret->h / 2, 2)))
				return (false);
		if (mrt->rcoef < 1.0f)
			if (!(fabs(vector_dot(
				vector_sub(hit, ret->pos), ret->e1)) < pow(ret->h / 2, 2)
				&& fabs(vector_dot(vector_sub(hit, ret->pos), ret->e2)) <
				pow(ret->h / 2, 2)))
				return (false);
		*t = dist;
		return (true);
	}
	return (false);
}

bool				raytracer_sq(t_mrt *mrt, t_ray *r, double *t)
{
	t_square	*ret;

	ret = NULL;
	mrt->cur_sq = mrt->sq;
	while (mrt->cur_sq)
	{
		mrt->cur_sq->r.start = r->start;
		mrt->cur_sq->r.dir = r->dir;
		if (intersect_square(mrt, mrt->cur_sq, r, t) == true)
			ret = mrt->cur_sq;
		mrt->cur_sq = mrt->cur_sq->next;
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
