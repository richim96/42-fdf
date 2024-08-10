/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/10 15:46:34 by rmei             ###   ########.fr       */
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

/* Apply DDA line drawing algorithm. */
static void	ft_dda_line_draw(t_img *img, t_vec_3D **vecs, int pos, int next)
{
	int			color;
	float		x;
	float		y;
	t_dda_line	line;

	color = vecs[pos]->color;
	if (vecs[pos]->z != vecs[pos + next]->z)
		color = vecs[pos + next]->color;
	line.delta_x = vecs[pos + next]->x - vecs[pos]->x;
    line.delta_y = vecs[pos + next]->y - vecs[pos]->y;
	if (abs(line.delta_x) > abs(line.delta_y))
		line.steps = abs(line.delta_x);
	else
		line.steps = abs(line.delta_y);
	line.step_x = line.delta_x / (float)line.steps;
	line.step_y = line.delta_y / (float)line.steps;
	x = (float)(vecs[pos]->x);
	y = (float)(vecs[pos]->y);
	while (line.steps-- >= 0)
	{
		ft_mlx_pxl_draw(img, round(x), round(y), color);
		x += line.step_x;
		y += line.step_y;
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
	next_row = screen->img->width + 1;
	while (screen->vecs[pos + next_row])
	{
		ft_dda_line_draw(screen->img, screen->vecs, pos, next_col);
		ft_dda_line_draw(screen->img, screen->vecs, pos, next_row);
		if (pos % 25 == 0)
			mlx_put_image_to_window(
				screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
				W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
		pos++;
	}
	while (screen->vecs[pos + next_col])
		ft_dda_line_draw(screen->img, screen->vecs, pos++, next_col);
	mlx_put_image_to_window(
		screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr,
		W_WIDTH * IX_POS, W_HEIGHT * IY_POS);
}
