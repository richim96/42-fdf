/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_manipulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 20:40:48 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_z_info_unpack(t_coord *coord, char *z_info)
{
	char	**z_coord_color;

	z_coord_color = ft_split(z_info, ',');
	coord->z = ft_atoi(z_coord_color[0]);
	if (z_coord_color[1])
		coord->pxl_color = ft_hextoi(z_coord_color[1]);
	else
		coord->pxl_color = ft_hextoi(STD_PXL_COLOR);
	free(z_coord_color[0]);
	free(z_coord_color[1]);
	free(z_coord_color);
}

static t_coord	*ft_coord_add(char *z_info, int x, int y)
{
	t_coord	*coord;

	coord = malloc(sizeof(t_coord));
	if (!coord)
		return (NULL);
	coord->x = x;
	coord->y = y;
	ft_z_info_unpack(coord, z_info);
	return (coord);
}

// TODO: Add malloc checks
static void	ft_vector_add(t_coord **coords, char *vector, int cols, int y)
{
	int			i;
	int			x;
	static int	j;
	char		**z_data;

	z_data = ft_split(vector, ' ');
	i = 0;
	x = 0;
	while (z_data[i])
	{
		coords[j] = ft_coord_add(z_data[i], x, y);
		if (!coords[i])
			;
		x += (IMG_WIDTH / cols);
		free(z_data[i++]);
		j++;
	}
	free(z_data);
}

// TODO: add mallock checks
t_coord	**ft_coords_make(char *map, int fd)
{
	int		n_cols;
	int		n_rows;
	int		y;
	char	*vector;
	t_coord	**coords;

	vector = ft_get_next_line(fd);
	if (!vector)
		return (NULL);
	n_cols = ft_n_cols(vector);
	n_rows = ft_n_rows(map);
	coords = malloc(((n_cols * n_rows) + 1) * sizeof(t_coord *));
	if (!coords)
		;
	coords[n_cols * n_rows] = (void *)0;
	y = 0;
	while (vector)
	{
		ft_vector_add(coords, vector, n_cols, y);
		y += (IMG_HEIGHT / n_rows);
		free(vector);
		vector = ft_get_next_line(fd);
	}
	return (coords);
}
