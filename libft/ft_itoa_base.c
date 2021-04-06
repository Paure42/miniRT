/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:34:37 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:34:40 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_base(int n, int base_max)
{
	int i;

	if (n < 0)
		i = 1;
	else if (n == 0)
		i = 1;
	else
		i = 0;
	while (n)
	{
		n /= base_max;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(int n, char *base)
{
	char	*str;
	int		k;
	int		negatif;
	int		base_max;

	base_max = ft_strlen(base);
	k = ft_count_base(n, base_max) + 1;
	if (!(str = ft_calloc(k, sizeof(char))))
		return (str = ft_calloc(1, sizeof(char)));
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
		negatif = 0;
	}
	else
		negatif = -1;
	k--;
	while (--k > negatif)
	{
		str[k] = base[n % base_max];
		n /= base_max;
	}
	return (str);
}
