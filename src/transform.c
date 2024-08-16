/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:53:58 by rmei              #+#    #+#             */
/*   Updated: 2024/08/16 12:45:37 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Zoom the image to fit the screen. */
static float	ft_zoom_set(t_limits *lmt)
{
	float	zoom;
	float	zoom_y;

	zoom = (float)I_WIDTH / (lmt->max_x - lmt->min_x);
	zoom_y = (float)I_HEIGHT / (lmt->max_y - lmt->min_y);
	if (zoom_y < zoom)
		zoom = zoom_y;
	return (zoom);
}

/* Move to coordinates to center the image in the screen. */
static void	ft_image_fit(t_limits *lmt, t_vec_3D **vecs, int zoom)
{
	int	i;
	int	offset_x;
	int	offset_y;

	i = 0;
	offset_x = (I_WIDTH - round((lmt->max_x - lmt->min_x))) / 2 - lmt->min_x;
	offset_y = (I_HEIGHT - round((lmt->max_y - lmt->min_y))) / 2 - lmt->min_y;
	while (vecs[i])
	{
		vecs[i]->x = round(vecs[i]->x * zoom) + offset_x;
		vecs[i]->y = round(vecs[i]->y * zoom) + offset_y;
		i++;
	}
}

/* Apply an isometric transformation on the map coordinates. */
void	ft_iso_transform(t_vec_3D **vecs)
{
	int			i;
	float		x;
	float		zoom;
	t_limits	lmt;
	t_vec_3D	*v;

	i = 0;
	while (vecs[i])
	{
		v = vecs[i];
		x = v->x;
		v->x = (x - v->y) * cos(ALPHA);
		v->y = (x + v->y) * sin(ALPHA) / 2 - v->z;
		i++;
	}
	ft_vec_limits_set(&lmt, vecs);
	zoom = ft_zoom_set(&lmt);
	lmt.max_x *= zoom;
	lmt.min_x *= zoom;
	lmt.max_y *= zoom;
	lmt.min_y *= zoom;
	ft_image_fit(&lmt, vecs, zoom);
}
