/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paure <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:55:22 by paure             #+#    #+#             */
/*   Updated: 2020/06/12 11:55:23 by paure            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void			create_window(t_mrt *mrt)
{
	if (mrt->error == 0 && (mrt->ali == -1 || mrt->rx == -1
	|| mrt->ry == -1 || mrt->cam == NULL))
	{
		ft_putstr_fd("Error, Resolution or Ambient light or ", 1);
		ft_putstr_fd("Camera are missing\n", 1);
		exit_prog(mrt);
		return ;
	}
	mrt->mlx_ptr = mlx_init();
	mrt->win_ptr = NULL;
	if ((mrt->win_ptr = mlx_new_window(mrt->mlx_ptr, mrt->rx, mrt->ry,
		"MiniRT")) == NULL)
		mrt->error = -1;
	mrt->cur_cam = mrt->cam;
	mrt->cur_li = mrt->li;
}

void			parsing_hub(t_mrt *mrt, char *str)
{
	if (str[0] == 'R' && str[1] == ' ')
		parsing_resolution(mrt, str);
	else if (str[0] == 'A' && str[1] == ' ')
		parsing_ambient_light(mrt, str);
	else if (str[0] == 'c' && str[1] == 'y' && str[2] == ' ')
		parsing_cylinder(mrt, str);
	else if (str[0] == 'c' && str[1] == ' ')
		parsing_camera(mrt, str);
	else if (str[0] == 'l' && str[1] == ' ')
		parsing_light(mrt, str);
	else if (str[0] == 's' && str[1] == 'p' && str[2] == ' ')
		parsing_sphere(mrt, str);
	else if (str[0] == 't' && str[1] == 'r' && str[2] == ' ')
		parsing_triangle(mrt, str);
	else if (str[0] == 's' && str[1] == 'q' && str[2] == ' ')
		parsing_square(mrt, str);
	else if (str[0] == 'p' && str[1] == 'l' && str[2] == ' ')
		parsing_plane(mrt, str);
	else if (str[0] == 'd' && str[1] == 'i' && str[2] == ' ')
		parsing_disk(mrt, str);
}

int				reading_file(t_mrt *mrt, int fd)
{
	char	*line;
	int		ret;

	mrt->error = 0;
	mrt->rx = -1;
	mrt->ry = -1;
	mrt->cam = NULL;
	mrt->li = NULL;
	mrt->sp = NULL;
	mrt->tr = NULL;
	mrt->sq = NULL;
	mrt->pl = NULL;
	mrt->cy = NULL;
	mrt->di = NULL;
	mrt->ali = -1;
	color_init(&mrt->argb);
	while ((ret = get_next_line(fd, &line)) != -1)
	{
		if (mrt->error == 0)
			parsing_hub(mrt, line);
		free(line);
		if (ret == 0)
			break ;
	}
	return (ret);
}

static int		check_args(t_mrt *mrt, int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr_fd("Please choose a .rt file\n", 1);
		return (-1);
	}
	if (argc > 3)
	{
		ft_putstr_fd("Too many arguments\n", 1);
		return (-1);
	}
	if (argc == 3)
	{
		if (ft_strcmp("--save", argv[2]) == 0)
			mrt->save = 1;
		else
		{
			ft_putstr_fd("Invalid arguments\n", 1);
			return (-1);
		}
	}
	return (0);
}

int				main(int argc, char **argv)
{
	int		fd;
	t_mrt	mrt;
	int		len;

	mrt.save = 0;
	mrt.img_ptr = NULL;
	if ((check_args(&mrt, argc, argv)) == -1)
		return (-1);
	len = ft_strlen(argv[1]);
	if (len < 4 || argv[1][len - 1] != 't' || argv[1][len - 2] != 'r'
		|| argv[1][len - 3] != '.')
	{
		ft_putstr_fd("Please choose a valid .rt file\n", 1);
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error opening file\n", 1);
		return (-1);
	}
	if (reading_file(&mrt, fd) == -1 || mrt.error == 1)
		exit_prog(&mrt);
	create_window(&mrt);
	raytracing_hub(&mrt);
	return (0);
}
