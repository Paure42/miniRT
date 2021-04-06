/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:29:31 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:29:33 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char const *s, char c)
{
	int i;
	int nbwords;

	if (!(s))
		return (0);
	i = 0;
	nbwords = 1;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i + 1] == c)
				i++;
			if (s[i + 1])
				nbwords++;
		}
		i++;
	}
	if (nbwords == 1 && s[0] == c)
		return (0);
	return (nbwords);
}
