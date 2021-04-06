/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <paure@student.le-101.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 14:09:18 by paure             #+#    #+#             */
/*   Updated: 2020/05/13 14:09:18 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

static void	init_bmp(t_mrt *mrt, t_bmp *bmp)
{
	bmp->file_type[0] = 0x42;
	bmp->file_type[1] = 0x4D;
	bmp->file_size = 54 + mrt->rx * mrt->ry * 3;
	bmp->reserved = 0;
	bmp->offset = 54;
	bmp->header_size = 40;
	bmp->img_width = mrt->rx;
	bmp->img_height = mrt->ry;
	bmp->planes = 1;
	bmp->bpp = 24;
	bmp->compression = 0;
	bmp->img_size = mrt->rx * mrt->ry * 3;
	bmp->x_pixels = 2835;
	bmp->y_pixels = 2835;
	bmp->total_colors = 0;
	bmp->important_colors = 0;
}

static void	write_header(t_bmp *bmp, int fd)
{
	write(fd, &(bmp->file_type), 2);
	write(fd, &(bmp->file_size), 4);
	write(fd, &(bmp->reserved), 4);
	write(fd, &(bmp->offset), 4);
	write(fd, &(bmp->header_size), 4);
	write(fd, &(bmp->img_width), 4);
	write(fd, &(bmp->img_height), 4);
	write(fd, &(bmp->planes), 2);
	write(fd, &(bmp->bpp), 2);
	write(fd, &(bmp->compression), 4);
	write(fd, &(bmp->img_size), 4);
	write(fd, &(bmp->x_pixels), 4);
	write(fd, &(bmp->y_pixels), 4);
	write(fd, &(bmp->total_colors), 4);
	write(fd, &(bmp->important_colors), 4);
}

void		bmp_save(t_mrt *mrt, int x, int y)
{
	int		fd;
	char	*content;
	t_bmp	bmp;
	int		line;

	if ((fd = open("output.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0777)) <= 0)
	{
		mrt->error = 1;
		no_leaks(mrt);
	}
	content = (char *)mrt->img_data;
	init_bmp(mrt, &bmp);
	write_header(&bmp, fd);
	y = mrt->ry - 1;
	while (y-- >= 0)
	{
		x = 0;
		while (x++ < mrt->rx)
		{
			line = (y * mrt->rx + x) * 4;
			write(fd, &(content[line]), 3);
		}
	}
	close(fd);
	ft_putstr_fd("Bmp file created\n", 1);
}
