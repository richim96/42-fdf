/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/10 14:41:55 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_ztoi(char *row);

static t_matrix	*ft_matrix_fill(int fd, t_matrix *matrix, )

t_matrix	*ft_matrix_extract(int fd)
{
	t_matrix	*matrix;
	char		**vertex;
	char		*line;
	int			cols;
	int			rows;
	int			i;

	matrix = malloc(sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	line = ft_get_next_line(fd);
	vertex = ft_split(line, ' ');
	cols = ft_strlen(vertex);
	matrix->x = malloc(cols);
	matrix->z = malloc(cols);
	if (!matrix->x || !matrix->z)
	{
		free(line);
		free(vertex);
		free(matrix->x);
		free(matrix->z);
		free(matrix);
		return (NULL);
	}
	i = 0;
	while (i < cols)
		matrix->x[rows] = i++;
	rows = 1;
	while (line)
	{
		matrix->y = ft_realloc(matrix->y, rows++);
		if (!matrix->y)
		{
			free(line);
			free(vertex);
			free(matrix->x);
			free(matrix);
			return (NULL);
		}
		matrix->y[rows - 1] = rows - 1;
		rows = 0;
		cols = ft_strlen(vertex);
		while (rows < cols)
			matrix->z[rows] = ft_ztoi
	}
	return (matrix);
}

t_matrix	*ft_matrix_rotate(t_matrix *matrix, int theta);
