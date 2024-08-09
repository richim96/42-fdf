/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/08/07 18:42:15 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Converts an hexadecimal (0xFFFFFF) number into decimal */
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

/* Counts the matrix rows */
void	ft_content_size_get(t_img *img, char *map)
{
	int		fd;
	int		max_x;
	int		max_y;
	char	*line;
	char	**coords;

	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	coords = ft_split(line, ' ');
	max_x = 0;
	max_y = 0;
	while (coords[max_x])
		free(coords[max_x++]);
	free(coords);
	while (line)
	{
		max_y++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	img->max_x = max_x;
	img->max_y = max_y;
}

void	ft_write_error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
}

/* Frees nested allocations in a double pointer */
void	ft_double_ptr_free(void **ptr, int pos, int reverse)
{
	if (reverse == TRUE)
		while (--pos >= 0)
			free(ptr[pos]);
	else
		while (ptr[pos])
			free(ptr[pos++]);
	free(ptr);
}
