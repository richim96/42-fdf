/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/09 20:25:50 by rmei             ###   ########.fr       */
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

/* Apply Bresenham line algorithm to draw the x-axis coordinates */
static void	ft_bres_x_draw(t_img *img, t_vector_3d **vecs, int pos)
{
	int	x;
	int	y;
	int	m;
	int	slope_err;
	int	color;

	x = vecs[pos]->x;
	y = vecs[pos]->y;
	m = (vecs[pos + 1]->y - y) * 2;
	slope_err = m - (vecs[pos + 1]->x - x);
	if (vecs[pos]->z == vecs[pos + 1]->z)
		color = vecs[pos]->pxl_color;
	else
		color = ft_hextoi(BG_COLOR);
	while (x <= vecs[pos + 1]->x)
	{
		ft_mlx_pxl_draw(img, x, y, color);
		slope_err += m;
		if (slope_err >= 0)
		{
			y++;
			slope_err -= (vecs[pos + 1]->x - x) * 2;
		}
		x++;
	}
}

/* Apply Bresenham line algorithm to draw the y-axis coordinates */
static void	ft_bres_y_draw(t_img *img, t_vector_3d **vecs, int pos)
{
	int	x;
	int	y;
	int	m;
	int	slope_err;
	int	color;

	x = vecs[pos]->x;
	y = vecs[pos]->y;
	m = (vecs[pos + img->max_x]->x - x) * 2;
	slope_err = m - (vecs[pos + img->max_x]->y - y);
	if (vecs[pos]->z == vecs[pos + img->max_x]->z)
		color = vecs[pos]->pxl_color;
	else
		color = vecs[pos + img->max_x]->pxl_color;
	while (y <= vecs[pos + img->max_x]->y)
	{
		ft_mlx_pxl_draw(img, x, y, color);
		slope_err += m;
		if (slope_err >= 0)
		{
			x++;
			slope_err -= (vecs[pos + img->max_x]->y - y) * 2;
		}
		y++;
	}
}

static void	ft_mlx_img_draw(t_screen *screen)
{
	int		pos;

	ft_iso_transform(screen->vecs, screen->img->max_x, screen->img->max_y);
	pos = 0;
	while (screen->vecs[pos + screen->img->max_x])
	{
		ft_bres_x_draw(screen->img, screen->vecs, pos);
		ft_bres_y_draw(screen->img, screen->vecs, pos);
		if (pos % 25 == 0)
			mlx_put_image_to_window(
				screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
				W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
		pos++;
	}
	mlx_put_image_to_window(
		screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
		W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
}

void	ft_map_show(char *map)
{
	t_screen	screen;
	t_img		img;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(
			screen.mlx_ptr, W_WIDTH, W_HEIGHT, map);
	img.img_ptr = mlx_new_image(screen.mlx_ptr, W_WIDTH, W_HEIGHT);
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
