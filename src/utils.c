/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 14:09:47 by rmei             ###   ########.fr       */
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
void	ft_map_size_get(t_img *img, char *map)
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
void	ft_nested_array_free(void **array, int pos, int reverse)
{
	if (reverse == TRUE)
		while (--pos >= 0)
			free(array[pos]);
	else
		while (array[pos])
			free(array[pos++]);
	free(array);
}

void	ft_error_write(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
}
