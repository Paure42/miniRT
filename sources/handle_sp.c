/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:10:20 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:10:21 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static bool		intersect_sphere(t_ray *r, t_sphere *s, double *t, int level)
{
	double		b;
	double		c;
	t_vector	dist;
	float		discr;

	if (level)
		s->save.a = vector_dot(s->r.dir, s->r.dir);
	dist = vector_sub(r->start, s->pos);
	b = 2 * vector_dot(r->dir, dist);
	c = vector_dot(dist, dist) - (s->radius * s->radius);
	discr = b * b - 4 * s->save.a * c;
	if (discr < 0)
		return (false);
	else
		return (find_closest_sp(discr, c, b, t));
}

bool			find_closest_sp(float discr, double c, double b, double *t)
{
	discr = sqrt(discr);
	c = (-b + discr) / 2;
	b = (-b - discr) / 2;
	if (c > b)
		c = b;
	if ((c > 0.001f) && (c < *t))
		*t = c;
	else
		return (false);
	return (true);
}

static bool		check_sphere(t_mrt *mrt, double *t, t_sphere *ret)
{
	double		tmp;

	tmp = *t;
	mrt->scaled = vector_scale(*t, ret->r.dir);
	mrt->new_start = vector_add(ret->r.start, mrt->scaled);
	mrt->n = vector_sub(mrt->new_start, ret->pos);
	*t = vector_dot(mrt->n, mrt->n);
	if (*t == 0)
	{
		*t = tmp;
		return (false);
	}
	*t = 1.0f / sqrt(*t);
	mrt->n = vector_scale(*t, mrt->n);
	mrt->ret = &ret->mat;
	mrt->n = vector_normalize(mrt->n);
	return (true);
}

bool			raytracer_sp(t_mrt *mrt, t_ray *r, double *t, int level)
{
	t_sphere	*ret;

	mrt->cur_sp = mrt->sp;
	ret = NULL;
	while (mrt->cur_sp)
	{
		mrt->cur_sp->r.start = r->start;
		mrt->cur_sp->r.dir = r->dir;
		mrt->cur_sp->save.a = vector_dot(mrt->cur_sp->r.dir,
				mrt->cur_sp->r.dir);
		if (intersect_sphere(&mrt->cur_sp->r, mrt->cur_sp, t, level) == true)
			ret = mrt->cur_sp;
		mrt->cur_sp = mrt->cur_sp->next;
	}
	if (ret != NULL)
		return ((check_sphere(mrt, t, ret)));
	return (false);
}
