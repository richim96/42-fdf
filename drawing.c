/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 20:42:09 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Minilibx wrapper to color a pixel at the right address */
static void	ft_mlx_pixel_draw(t_img *img, int x, int y, unsigned int color)
{
	unsigned int	bytes_per_pixel;
	unsigned int	offset;
	char			*pixel_ptr;

	bytes_per_pixel = img->bits_per_pixel / 8;
	offset = y * img->size_line + x * bytes_per_pixel;
	pixel_ptr = img->img_addr + offset;
	*(unsigned int *)pixel_ptr = color;
}

static void	ft_mlx_img_draw(t_screen *screen)
{
	int		i;
	t_coord	*coord;

	i = 0;
	while (screen->coords[i])
	{
		coord = screen->coords[i];
		ft_mlx_pixel_draw(
			screen->img, coord->x, coord->y, coord->pxl_color);
		if (i % 15 == 0)
			mlx_put_image_to_window(
				screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
				WIN_WIDTH * IMG_W_POS_COEFF, WIN_HEIGHT * IMG_H_POS_COEFF
				);
		i++;
	}
}

static void	ft_mlx_events_init(t_screen *screen)
{
	mlx_hook(screen->win_ptr, ON_DESTROY, MLX_MASK, ft_mlx_kill, screen);
	mlx_key_hook(screen->win_ptr, ft_keyhook, screen);
}

void	ft_map_show(char *map)
{
	t_screen	screen;
	t_img		img;
	int			fd;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(
			screen.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, map);
	screen.img = &img;
	img.img_ptr = mlx_new_image(screen.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	fd = open(map, O_RDONLY);
	screen.coords = ft_coords_make(map, fd);
	close(fd);
	ft_mlx_events_init(&screen);
	ft_mlx_img_draw(&screen);
	mlx_loop(screen.mlx_ptr);
}
