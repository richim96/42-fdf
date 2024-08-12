/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/08/07 20:07:28 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Unpack the z-point info provided by the map (value and color). */
static void	ft_z_info_unpack(t_vec_3D *vec, char *z_info)
{
	char	**z_value_color;

	z_value_color = ft_split(z_info, ',');
	vec->z = ft_atoi(z_value_color[0]);
	if (z_value_color[1])
		vec->color = ft_hextoi(z_value_color[1]);
	else
	{
		if (vec->z != 0)
			vec->color = ft_hextoi(PXL_WHITE);
		else
			vec->color = ft_hextoi(BG_COLOR);
	}
	free(z_value_color[0]);
	free(z_value_color[1]);
	free(z_value_color);
}

/* Create a 3D vector, extracting the relevant coordinate data. */
static t_vec_3D	*ft_vector_make(char *z_info, int x, int y)
{
	t_vec_3D	*vec;

	vec = malloc(sizeof(t_vec_3D));
	if (!vec)
		return (NULL);
	vec->x = x;
	vec->y = y;
	ft_z_info_unpack(vec, z_info);
	return (vec);
}

/* Add a 3D vector to the existing vector array. */
static t_vec_3D	**ft_vector_add(t_vec_3D **vecs, char *vec, int y)
{
	int			x;
	static int	j;
	char		**z_data;

	z_data = ft_split(vec, ' ');
	x = 0;
	while (z_data[x])
	{
		vecs[j] = ft_vector_make(z_data[x], x, y);
		if (!vecs[j])
		{
			ft_nested_array_free((void **)vecs, j, TRUE);
			ft_nested_array_free((void **)z_data, x, FALSE);
			return (NULL);
		}
		free(z_data[x]);
		x++;
		j++;
	}
	free(z_data);
	return (vecs);
}

/* Create the 3D vector array from which to draw the image to screen. */
t_vec_3D	**ft_vectors_make(t_img *img, char *map)
{
	int			y;
	int			fd;
	char		*line;
	t_vec_3D	**vecs;

	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	vecs = ft_calloc((img->width * img->height) + 1, sizeof(t_vec_3D *));
	if (!vecs)
		free(line);
	else
	{
		y = 0;
		while (line)
		{
			vecs = ft_vector_add(vecs, line, y);
			free(line);
			if (!vecs)
				break ;
			line = ft_get_next_line(fd);
			y++;
		}
	}
	close(fd);
	return (vecs);
}
