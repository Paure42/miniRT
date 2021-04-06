/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:27:20 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:48:23 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	ret;
	double	tmp;
	int		neg;

	ret = 0;
	neg = 1;
	tmp = 0;
	while (*str && *str != '-' && (*str < '0' || *str > '9'))
		str++;
	ret = (float)ft_atoi(str);
	if (ret < 0)
		str++;
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str == '.' && *str++)
		tmp = (float)ft_atoi(str);
	while (tmp >= 1.0f)
		tmp *= 0.1;
	ret += tmp;
	return (ret * neg);
}
