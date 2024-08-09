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
static void	ft_mlx_pxl_draw(t_img *img, int x, int y, unsigned int color)
{
	unsigned int	bytes_per_pixel;
	unsigned int	offset;
	char			*pixel_ptr;

	bytes_per_pixel = img->bits_per_pixel / 8;
	offset = x * bytes_per_pixel + y * img->size_line;
	pixel_ptr = img->img_addr + offset;
	*(unsigned int *)pixel_ptr = color;
}

static void	ft_mlx_line_draw(t_img *img, t_vector_3d **vecs, int pos)
{
	// int			x1;
	// int			y1;
	// int			x_end;
	// int			y_end;
	t_vector_3d	*start;

	start = vecs[pos];
	// x_end = vecs[pos + 1]->x;
	// while (x_end >= start->x)
	// {
	// 	y1 = start->y + start->z;
	// 	ft_mlx_pxl_draw(img, x_end--, y1, start->pxl_color);
	// 	;
	// }
	// y_end = vecs[pos + img->max_x]->y;
	// while (y_end >= start->y)
	// {
	// 	y1 = y_end + start->z;
	// 	ft_mlx_pxl_draw(img, start->x, y1, start->pxl_color);
	// 	y_end--;
	// }
	// x1 = start->x - start->y;
	// y1 = (start->x + start->y) / 2 - start->z;
	ft_mlx_pxl_draw(img, start->x, start->y, start->pxl_color);
}

static void	ft_mlx_img_draw(t_screen *screen)
{
	int		pos;

	pos = 0;
	while (screen->vecs[pos]) // + screen->img->max_x])
	{
		ft_mlx_line_draw(screen->img, screen->vecs, pos);
		pos++;
	}
	mlx_put_image_to_window(
		screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
		WIN_WIDTH * IMG_W_POS_COEFF, WIN_HEIGHT * IMG_H_POS_COEFF
		);
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
	screen.vecs = ft_vectors_make(screen.img, map);
	if (!screen.vecs)
	{
		ft_write_error("[ERROR]: Not enough memory available for this map\n");
		ft_mlx_kill(&screen);
	}
	ft_mlx_events_init(&screen);
	ft_mlx_img_draw(&screen);
	mlx_loop(screen.mlx_ptr);
}
