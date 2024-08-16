/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/08/16 12:16:48 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Convert a hexadecimal (0xFFFFFF) number to decimal base. */
int	ft_hextoi(char *hex)
{
	int	n;
	int	n_pow;
	int	result;

	result = 0;
	if (hex[1] == 'x')
		hex += 2;
	n_pow = ft_strlen(hex) - 1;
	while (*hex)
	{
		if (ft_isalpha(*hex))
			n = ft_tolower(*hex) - 'a' + 10;
		else
			n = *hex - '0';
		result += n * pow(16, n_pow);
		n_pow--;
		hex++;
	}
	return (result);
}

/* Compute the size of the map. */
void	ft_map_size_set(t_img *img, char *map)
{
	int		fd;
	int		width;
	int		height;
	char	*line;
	char	**coords;

	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	coords = ft_split(line, ' ');
	width = 0;
	height = 0;
	while (coords[width])
		free(coords[width++]);
	free(coords);
	while (line)
	{
		height++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	img->width = width;
	img->height = height;
}

/* Free memory from a bidimensional array. */
void	ft_nested_arr_free(void **arr, int pos, int reverse)
{
	if (reverse == TRUE)
		while (--pos >= 0)
			free(arr[pos]);
	else
		while (arr[pos])
			free(arr[pos++]);
	free(arr);
}

void	ft_error_write(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
}

/* Get the min and max (X, Y) values from a 1D matrix. */
void	ft_vec_limits_set(t_limits *limits, t_vec_3D **vecs)
{
	int			i;
	t_vec_3D	*v;

	i = 0;
	limits->min_x = 0;
	limits->max_x = 0;
	limits->min_y = 0;
	limits->max_y = 0;
	while (vecs[i])
	{
		v = vecs[i];
		if (v->x < limits->min_x)
			limits->min_x = v->x;
		if (v->x > limits->max_x)
			limits->max_x = v->x;
		if (v->y < limits->min_y)
			limits->min_y = v->y;
		if (v->y > limits->max_y)
			limits->max_y = v->y;
		i++;
	}
}
