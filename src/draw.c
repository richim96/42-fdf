/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/13 16:54:55 by rmei             ###   ########.fr       */
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

static void	ft_bres_line_set(t_bres_line *line, t_vec_3D *vec1, t_vec_3D *vec2)
{
	line->x = vec1->x;
	line->y = vec1->y;
	line->dx = abs(vec2->x - vec1->x);
	line->dy = -abs(vec2->y - vec1->y);
	line->sx = 1;
	if (vec2->x < vec1->x)
		line->sx = -1;
	line->sy = 1;
	if (vec2->y < vec1->y)
		line->sy = -1;
	line->e = line->dx + line->dy;
	line->color = vec1->color;
	if (vec1->z == 0)
		line->color = vec2->color;
}

/* Draws a line from point A to point B using the DDA algorithm. */
static void	ft_bres_line_draw(t_img *img, t_vec_3D *vec1, t_vec_3D *vec2)
{
	t_bres_line	line;

	ft_bres_line_set(&line, vec1, vec2);
	while (!(line.x == vec2->x && line.y == vec2->y))
	{
		ft_mlx_pxl_draw(img, line.x, line.y, line.color);
		line.e2 = line.e * 2;
		if (line.e2 > line.dy)
		{
			line.e += line.dy;
			line.x += line.sx;
		}
		if (line.e2 < line.dx)
		{
			line.e += line.dx;
			line.y += line.sy;
		}
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
		if ((pos + 1) % row_len != 0)
			ft_bres_line_draw(
				screen->img, screen->vecs[pos], screen->vecs[pos + 1]);
		if (pos < row_limit)
			ft_bres_line_draw(
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
