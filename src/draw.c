/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/13 13:05:04 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Minilibx wrapper to set pixel color at the right address. */
static void	ft_mlx_pxl_draw(t_img *img, int x, int y, unsigned int color)
{
	unsigned int	bytes_pxl;
	unsigned int	offset;
	char			*pxl_color;

	bytes_pxl = img->bits_pixel / 8;
	offset = x * bytes_pxl + y * img->size_line;
	pxl_color = img->img_addr + offset;
	*(unsigned int *)pxl_color = color;
}

/* Draws a line from point A to point B using the DDA algorithm. */
static void	ft_dda_line_draw(t_img *img, t_vec_3D *vec1, t_vec_3D *vec2)
{
	int		color;
	int		x;
	int		y;
	float	slope;

	color = vec1->color;
	if (vec1->z == 0)
		color = vec2->color;
	slope = (vec2->x - vec1->x) / (float)(vec2->y - vec1->y);
	y = vec1->y;
	while (y <= vec2->y)
	{
		x = round(vec1->x + slope * (y - vec1->y));
		ft_mlx_pxl_draw(img, x, y, color);
		y++;
	}
}

/* Draw the image to screen. */
void	ft_map_draw(t_screen *screen)
{
	int	pos;
	int	row_len;
	int	row_limit;

	pos = 0;
	row_len = screen->img->width;
	row_limit = row_len * (screen->img->height - 1);
	ft_iso_transform(screen->vecs, screen->img->width, screen->img->height);
	while (screen->vecs[pos + 1])
	{
		ft_dda_line_draw(
			screen->img, screen->vecs[pos], screen->vecs[pos + 1]);
		if (pos < row_limit)
			ft_dda_line_draw(
				screen->img, screen->vecs[pos], screen->vecs[pos + row_len]);
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
