/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmpchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:28:38 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:28:42 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cmpchar(char const *s1, char const *set, int start, int pos)
{
	int i;

	i = -1;
	if (!(s1) || !(set))
		return (0);
	while (set[++i] && start != -1 && s1[start])
	{
		if (set[i] == s1[start])
		{
			start += pos;
			i = -1;
		}
	}
	return (start);
}
