/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:09:34 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:09:36 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

char		*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		n;

	n = -1;
	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return ((ft_strdup(s2)));
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (0);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++n])
	{
		str[i] = s2[n];
		i++;
	}
	str[i] = 0;
	free((char*)s1);
	return (str);
}

char		*gnl_substr(char const *s, unsigned int start, size_t len, int f)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	str = NULL;
	i = ft_strlen(s);
	if (start >= i)
		return (free_strs((char*)s, str));
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (free_strs((char*)s, str));
	i = 0;
	while (i < len)
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = 0;
	if (f == 1)
		free((char*)s);
	return (str);
}
