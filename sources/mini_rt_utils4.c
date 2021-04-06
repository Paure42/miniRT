/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:48:39 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 11:58:30 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

t_vector			new_vec3(double x, double y, double z)
{
	t_vector ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

unsigned int		min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
