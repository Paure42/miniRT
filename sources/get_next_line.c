/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:09:25 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:09:26 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

char		*free_strs(char *s1, char *s2)
{
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	if (s2)
	{
		free(s2);
		s2 = NULL;
	}
	return (0);
}

int			gnl_strchr(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

char		*ft_strdup(const char *s1)
{
	int		n;
	char	*dest;

	n = 0;
	dest = 0;
	while (s1[n])
		n++;
	if (!(dest = malloc((n + 1) * sizeof(char))))
		return (free_strs((char*)s1, NULL));
	n = 0;
	while (s1[n])
	{
		dest[n] = s1[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

char		*readline(int fd, char *str)
{
	char	*buff;
	int		i;

	if (!str)
		if (!(str = (char*)ft_calloc(1, sizeof(char))))
			return (0);
	if (!(buff = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (free_strs(str, buff));
	while ((i = gnl_strchr(str, '\n')) == 0)
	{
		if ((i = read(fd, buff, BUFFER_SIZE)) < 0)
			return (free_strs(str, buff));
		buff[i] = 0;
		if (!(str = gnl_strjoin(str, buff)))
			return (free_strs(str, buff));
		if (str[0] == 0 || i == 0 || i < BUFFER_SIZE)
			break ;
	}
	if (buff)
		free(buff);
	return (str);
}

int			get_next_line(int fd, char **line)
{
	static char	*str = NULL;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || !(str = readline(fd, str)))
		return (-1);
	if ((i = gnl_strchr(str, '\n')) > 0)
	{
		if (i == 1)
			*line = ft_strdup("");
		else if (!(*line = gnl_substr(str, 0, i - 1, 0)))
			return (-1);
		str = gnl_substr(str, i, ft_strlen(str) - i, 1);
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(str)))
			return (-1);
		if (str)
			free(str);
		str = NULL;
		return (0);
	}
}
