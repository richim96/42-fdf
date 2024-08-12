/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 22:10:28 by rmei             ###   ########.fr       */
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

/* Set info for the current line used in Bresenham algorithm. */
static void	ft_line_set(t_bres_line *line, t_vec_3D *vec1, t_vec_3D *vec2)
{
	line->dx = vec2->x - vec1->x;
	line->dy = vec2->y - vec1->y;
	line->m = line->dx - line->dy;
	line->step_x = 1;
	if (line->dx < 0)
		line->step_x = -1;
	line->step_y = 1;
	if (line->dy < 0)
		line->step_y = -1;
	line->dx = abs(line->dx);
	line->dy = abs(line->dy);
	line->color = vec1->color;
	if (vec1 == 0)
		line->color = vec2->color;
}

/* Apply Bresenham line drawing algorithm. */
void	ft_line_draw(t_img *img, t_vec_3D *vec1, t_vec_3D *vec2)
{
	int			x;
	int			y;
	t_bres_line	line;

	x = vec1->x;
	y = vec1->y;
	ft_line_set(&line, vec1, vec2);
	while (x <= vec2->x && y <= vec2->y)
	{
		ft_mlx_pxl_draw(img, x, y, line.color);
		line.e = line.m * 2;
		if (line.e > -line.dy)
		{
			line.m -= line.dy;
			x += line.step_x;
		}
		if (line.e < line.dx)
		{
			line.m += line.dx;
			y += line.step_y;
		}
	}
}

/* Apply DDA line drawing algorithm on the y-axis. */
void	ft_dda_line_draw(t_img *img, t_vec_3D *vec1, t_vec_3D *vec2)
{
	int		color;
	int		x;
	int		y;
	float	slope;

	color = vec1->color;
	if (vec1->z == 0)
		color = vec2->color;
	slope = (vec2->y - vec1->y) / (float)(vec2->x - vec1->x);
	x = vec1->x;
	while (x <= vec2->x)
	{
		y = round(vec1->y + slope * (x - vec1->x));
		ft_mlx_pxl_draw(img, x, y, color);
		x++;
	}
}

/* Draw the image to screen. */
void	ft_map_draw(t_screen *screen)
{
	int	pos;
	int	add_row;

	ft_iso_transform(screen->vecs, screen->img->width, screen->img->height);
	pos = 0;
	add_row = screen->img->width;
	while (screen->vecs[pos + 1])
	{
		//ft_line_draw(screen->img, screen->vecs[pos], screen->vecs[pos + 1]);
		ft_dda_line_draw(
			screen->img, screen->vecs[pos], screen->vecs[pos + 1]);
		if (pos < (add_row * (screen->img->height - 1)))
			ft_dda_line_draw(
				screen->img, screen->vecs[pos], screen->vecs[pos + add_row]);
		// 	ft_line_draw(
		// 		screen->img, screen->vecs[pos], screen->vecs[pos + add_row]);
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
