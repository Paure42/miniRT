/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:50:33 by paure             #+#    #+#             */
/*   Updated: 2020/06/03 15:50:34 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static	void	sort(t_triangle *tr)
{
	int			check;
	t_vector	tmp;

	while (1)
	{
		check = 0;
		if (tr->pos1.y > tr->pos2.y)
		{
			tmp = tr->pos1;
			tr->pos1 = tr->pos2;
			tr->pos2 = tmp;
			check = 1;
		}
		if (tr->pos2.y > tr->pos3.y)
		{
			tmp = tr->pos2;
			tr->pos2 = tr->pos3;
			tr->pos3 = tmp;
			check = 1;
		}
		if (check == 0)
			break ;
	}
}

void			compute_tr(t_mrt *mrt)
{
	mrt->cur_tr = mrt->tr;
	while (mrt->cur_tr)
	{
		sort(mrt->cur_tr);
		mrt->cur_tr->v0v1 = vector_sub(mrt->cur_tr->pos2, mrt->cur_tr->pos1);
		mrt->cur_tr->v0v2 = vector_sub(mrt->cur_tr->pos3, mrt->cur_tr->pos1);
		mrt->cur_tr->v1v2 = vector_sub(mrt->cur_tr->pos2, mrt->cur_tr->pos3);
		mrt->cur_tr->normal = vector_cross(mrt->cur_tr->v0v1,
				mrt->cur_tr->v0v2);
		mrt->cur_tr->normal = vector_normalize(mrt->cur_tr->normal);
		mrt->cur_tr = mrt->cur_tr->next;
	}
}

static bool		intersect_triangle(t_triangle *ret, t_ray *r, double *t)
{
	t_vector	t_vec;
	double		det;

	ret->pvec = vector_cross(r->dir, ret->v0v2);
	if (fabs((det = vector_dot(ret->v0v1, ret->pvec))) < EPSILON)
		return (false);
	det = 1 / det;
	t_vec = vector_sub(r->start, ret->pos1);
	ret->u = vector_dot(t_vec, ret->pvec) * det;
	if (ret->u < 0 || ret->u > 1)
		return (false);
	t_vec = vector_cross(t_vec, ret->v0v1);
	ret->v = vector_dot(r->dir, t_vec) * det;
	if (ret->v < 0 || (ret->u + ret->v) > 1)
		return (false);
	ret->z1 = vector_scale(ret->u, ret->v0v1);
	ret->z2 = vector_scale(ret->v, ret->v0v2);
	ret->z3 = vector_scale(1.0f - ret->u - ret->v, ret->v1v2);
	t_vec = vector_add(vector_add(ret->z1, ret->z2), ret->z3);
	det = calc_dist_fabs(t_vec, r->start);
	if (det > *t || det < 0)
		return (false);
	*t = det;
	ret->z3 = t_vec;
	return (true);
}

bool			raytracer_tr(t_mrt *mrt, t_ray *r, double *t)
{
	t_triangle *ret;

	mrt->cur_tr = mrt->tr;
	ret = NULL;
	while (mrt->cur_tr)
	{
		mrt->cur_tr->mat.rgb.r = mrt->cur_tr->save.a;
		mrt->cur_tr->mat.rgb.g = mrt->cur_tr->save.b;
		mrt->cur_tr->mat.rgb.b = mrt->cur_tr->save.c;
		mrt->cur_tr->r.start = r->start;
		mrt->cur_tr->r.dir = r->dir;
		if (intersect_triangle(mrt->cur_tr, &mrt->cur_tr->r, t) == true)
			ret = mrt->cur_tr;
		mrt->cur_tr = mrt->cur_tr->next;
	}
	if (ret == NULL)
		return (false);
	mrt->new_start = vector_add(ret->r.start, vector_scale(*t, ret->r.dir));
	mrt->n = vector_normalize(ret->z3);
	ret->mat.rgb.r *= ret->u;
	ret->mat.rgb.g *= ret->v;
	ret->mat.rgb.b *= (1 - ret->u - ret->v);
	mrt->ret = &ret->mat;
	return (true);
}
