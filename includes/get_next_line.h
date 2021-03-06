/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 11:39:18 by paure             #+#    #+#             */
/*   Updated: 2020/05/15 11:45:48 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# define BUFFER_SIZE 1

int		get_next_line(int fd, char **line);
char	*readline(int fd, char *str);
char	*free_strs(char *s1, char *s2);
int		gnl_strchr(const char *s, char c);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*gnl_substr(char const *s, unsigned int start, size_t len, int f);
#endif
