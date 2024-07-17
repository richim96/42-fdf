/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/17 13:28:56 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**ft_z_coords_normalize(char **z_coords)
{
	return (z_coords);
}

/* Returns 1 upon successfully adding the nodes for the current vector */
static int	ft_vector_populate(t_list **matrix, char **z_coords, int x, int y)
{
	t_list	*node;
	int		*vector;

	while (*z_coords)
	{
		vector = malloc(3);
		if (!vector)
			return (0);
		vector[0] = x++;
		vector[1] = y;
		vector[2] = ft_atoi(*z_coords);
		node = ft_lstnew(vector);
		if (!node)
			return (0);
		ft_lstadd_back(matrix, node);
		z_coords++;
	}
	return (1);
}

static void	ft_matrix_populate(int fd, char *line, t_list **matrix)
{
	int		x;
	int		y;
	int		is_vector;
	char	**z_coords;

	x = 0;
	y = 0;
	while (line)
	{
		z_coords = ft_z_coords_normalize(ft_split(line, ' '));
		free(line);
		is_vector = ft_vector_populate(matrix, z_coords, x, y);
		if (!is_vector)
		{
			ft_lstclear(matrix, free);
			return ;
		}
		line = ft_get_next_line(fd);
		y++;
	}
}

t_list	**ft_matrix_make(char *map_path)
{
	t_list	**matrix;
	t_list	*__head;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	line = ft_get_next_line(fd);
	__head = NULL;
	matrix = &__head;
	ft_matrix_populate(fd, line, matrix);
	close(fd);
	return (matrix);
}

void	ft_matrix_rotate(t_list **matrix, int theta);
