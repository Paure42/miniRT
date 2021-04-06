/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countletters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:28:58 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:29:00 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countletters(char const *s, char c, int start)
{
	int	nbchar;

	if (!(s))
		return (0);
	nbchar = 0;
	while (s[start] != c && s[start])
	{
		start++;
		nbchar++;
	}
	return (nbchar);
}
