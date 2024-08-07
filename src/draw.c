/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/07 19:37:35 by rmei             ###   ########.fr       */
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
	offset = x * bytes_per_pixel + y * img->size_line;
	pixel_ptr = img->img_addr + offset;
	*(unsigned int *)pixel_ptr = color;
}


static void	ft_mlx_line_draw(t_img *img, t_vector_3d *vector)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = 0;
	pixel_y = 0;
	ft_mlx_pixel_draw(img, vector->x, vector->y, vector->pxl_color);
}


static void	ft_mlx_img_draw(t_screen *screen)
{
	int		i;

	i = 0;
	while (screen->vectors[i + 1])
	{
		ft_mlx_line_draw(screen->img, screen->vectors[i]);	
		if (i % 30 == 0)
			mlx_put_image_to_window(
				screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
				WIN_WIDTH * IMG_W_POS_COEFF, WIN_HEIGHT * IMG_H_POS_COEFF
				);
		i++;
	}
}


void	ft_map_show(char *map)
{
	t_screen	screen;
	t_img		img;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(
			screen.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, map);
	img.img_ptr = mlx_new_image(screen.mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	ft_content_size_get(&img, map);
	screen.img = &img;
	screen.vectors = ft_vectors_make(screen.img, map);
	if (!screen.vectors)
	{
		ft_write_error("[ERROR]: Not enough memory available for this map\n");
		ft_mlx_kill(&screen);
	}
	ft_mlx_events_init(&screen);
	ft_mlx_img_draw(&screen);
	mlx_loop(screen.mlx_ptr);
}
