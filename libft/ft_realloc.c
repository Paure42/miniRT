/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:40:07 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 13:40:08 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t size)
{
	char	*str;

	if (old_size > size)
		old_size = size;
	if (!ptr || !(str = ft_calloc(size, sizeof(char))))
		return (NULL);
	ft_memcpy(str, ptr, old_size);
	free(ptr);
	return (str);
}
