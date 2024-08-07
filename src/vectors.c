/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/08/07 20:07:28 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Unpacks the z-point info provided by the map (value and color) */
static void	ft_z_info_unpack(t_vector_3d *vector, char *z_info)
{
	char	**z_value_color;

	z_value_color = ft_split(z_info, ',');
	vector->z = ft_atoi(z_value_color[0]);
	if (z_value_color[1])
		vector->pxl_color = ft_hextoi(z_value_color[1]);
	else
	{
		if (vector->z > 0)
			vector->pxl_color = ft_hextoi(PXL_WHITE);
		else
			vector->pxl_color = ft_hextoi(PXL_MAROON	);
	}
	free(z_value_color[0]);
	free(z_value_color[1]);
	free(z_value_color);
}

/* Creates a 3D vector, extracting the relevant coordinate data */
static t_vector_3d	*ft_vector_make(char *z_info, int x, int y)
{
	t_vector_3d	*vector;

	vector = malloc(sizeof(t_vector_3d));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	ft_z_info_unpack(vector, z_info);
	return (vector);
}

/* Adds a 3D vector to the existing vector array */
static t_vector_3d	**ft_vector_add(t_vector_3d **vectors, char *vector, int y)
{
	int			x;
	static int	j;
	char		**z_data;

	z_data = ft_split(vector, ' ');
	x = 0;
	while (z_data[x])
	{
		vectors[j] = ft_vector_make(z_data[x], x, y);
		if (!vectors[j])
		{
			while (--j >= 0)
				free(vectors[j]);
			free(vectors);
			vectors = NULL;
			while (z_data[x])
				free(z_data[x++]);
			break ;
		}
		free(z_data[x]);
		x++;
		j++;
	}
	free(z_data);
	return (vectors);
}

/* Creates the 3D vector array from which to draw the image to screen */
t_vector_3d	**ft_vectors_make(t_img *img, char *map)
{
	int		y;
	int		fd;
	char	*line;
	t_vector_3d	**vectors;

	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	vectors = ft_calloc((img->n_cols * img->n_rows) + 1, sizeof(t_vector_3d *));
	if (!vectors)
		free(line);
	else
	{
		y = 0;
		while (line)
		{
			vectors = ft_vector_add(vectors, line, y++);
			free(line);
			if (!vectors)
				break ;
			line = ft_get_next_line(fd);
		}
	}
	close(fd);
	return (vectors);
}
