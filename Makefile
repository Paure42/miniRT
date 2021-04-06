# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paure <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/15 13:48:55 by paure             #+#    #+#              #
#    Updated: 2020/05/18 12:11:27 by paure            ###   ########.lyon.fr   #
#                                                                              #
# **************************************************************************** #

CC = clang

SOURCES = check_error.c \
		  bmp_save.c \
		  get_next_line.c \
		  get_next_line_utils.c \
		  handle_light.c \
		  handle_cy.c \
		  handle_sq.c \
		  handle_pl.c \
		  handle_sp.c \
		  handle_tr.c \
		  handle_key.c \
		  handle_di.c \
		  init.c \
		  lst_camera.c \
		  lst_light.c \
		  lst_plane.c \
		  lst_sphere.c \
		  lst_square.c \
		  lst_triangle.c \
		  lst_cylinder.c \
		  lst_disk.c \
		  mini_rt.c \
		  mini_rt_utils.c \
		  mini_rt_utils2.c \
		  mini_rt_utils3.c \
		  mini_rt_utils4.c \
		  no_leaks.c \
		  parsing_ambient_light.c \
		  parsing_camera.c \
		  parsing_cylinder.c \
		  parsing_disk.c \
		  parsing_light.c \
		  parsing_plane.c \
		  parsing_resolution.c \
		  parsing_sphere.c \
		  parsing_square.c \
		  parsing_triangle.c \
		  raytracing.c \

NAME = miniRT

MLXFLAGS= -I /usr/include -g3 -L /usr/lib -lX11 -lXext -IGLU -lm -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

LIBFT = libft

MLX   = minilibx-linux

DIR_S = sources

HD = includes

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_S)/,$(SOURCES:.c=.o))

all: $(NAME)

bonus:	${NAME}

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	@make -C $(MLX)
	@$(CC) $(OBJS) -I $(HD) $(MLXFLAGS) $(CFLAGS) $(MLX)/libmlx_Linux.a $(LIBFT)/libft.a -o $(NAME)
	@echo "miniRT executable is ready, choose a .rt file and enjoy !"
	
clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)
	make clean -C $(MLX)

fclean: clean
	rm -f $(NAME)
	make clean -C $(MLX)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
