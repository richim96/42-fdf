/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 18:53:03 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Minilibx wrapper to color a pixel at the right address. */
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

/* Apply DDA line drawing algorithm on the x-axis. */
void	ft_dda_x_draw(t_img *img, t_vec_3D **vecs, int pos, int next)
{
	int		color;
	int		x;
	int		y;
	float	slope;

	if (vecs[pos]->z != 0)
		color = vecs[pos]->color;
	else
		color = vecs[pos + next]->color;
	slope = (
			(vecs[pos + next]->y - vecs[pos]->y)
			/ (float)(vecs[pos + next]->x - vecs[pos]->x)
			);
	x = vecs[pos]->x;
	while (x <= vecs[pos + next]->x)
	{
		y = round(vecs[pos]->y + slope * (x - vecs[pos]->x));
		ft_mlx_pxl_draw(img, x, y, color);
		x++;
	}
}

/* Apply DDA line drawing algorithm on the y-axis. */
void	ft_dda_y_draw(t_img *img, t_vec_3D **vecs, int pos, int next)
{
	int		color;
	int		y;
	int		x;
	float	slope;

	if (vecs[pos]->z != 0)
		color = vecs[pos]->color;
	else
		color = vecs[pos + next]->color;
	slope = (
			(vecs[pos + next]->x - vecs[pos]->x)
			/ (float)(vecs[pos + next]->y - vecs[pos]->y)
			);
	y = vecs[pos]->y;
	while (y <= vecs[pos + next]->y)
	{
		x = round(vecs[pos]->x + slope * (y - vecs[pos]->y));
		ft_mlx_pxl_draw(img, x, y, color);
		y++;
	}
}

/* Draw the image to screen. */
void	ft_map_draw(t_screen *screen)
{
	int	pos;
	int	next_col;
	int	next_row;

	ft_iso_transform(screen->vecs, screen->img->width, screen->img->height);
	pos = 0;
	next_col = 1;
	next_row = screen->img->width;
	while (screen->vecs[pos + next_row + 1])
	{
		ft_dda_x_draw(screen->img, screen->vecs, pos, next_col);
		//ft_dda_y_draw(screen->img, screen->vecs, pos, next_row);
		if (pos % 25 == 0)
			mlx_put_image_to_window(
				screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
				W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
		pos++;
	}
	while (screen->vecs[pos + next_col + 1])
		ft_dda_x_draw(screen->img, screen->vecs, pos++, next_col);
	mlx_put_image_to_window(
		screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
		W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
}
