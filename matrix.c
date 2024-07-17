/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/17 18:59:02 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**ft_z_coords_normalize(char **z_coords)
{
	return (z_coords);
}

/* Returns 1 upon successfully adding the nodes for the current vector */
static t_list	*ft_vector_populate(t_list *matrix, char **z_coords, int x, int y)
{
	t_list	*node_new;
	int		*vector_new;

	while (*z_coords)
	{
		vector_new = malloc(3);
		if (!vector_new)
		{
			ft_lstclear(&matrix, free);
			break ;
		}
		vector_new[0] = x++;
		vector_new[1] = y;
		vector_new[2] = ft_atoi(*z_coords);
		node_new = ft_lstnew(vector_new);
		if (!node_new)
		{
			ft_lstclear(&matrix, free);
			break ;
		}
		matrix = ft_lstadd_back(matrix, node_new);
		z_coords++;
	}
	return (matrix);
}

static t_list	*ft_matrix_populate(int fd, char *line, t_list *matrix)
{
	int		x;
	int		y;
	char	**z_coords;

	x = 0;
	y = 0;
	while (line)
	{
		z_coords = ft_z_coords_normalize(ft_split(line, ' '));
		free(line);
		matrix = ft_vector_populate(matrix, z_coords, x, y);
		if (!matrix)
			return (NULL);
		line = ft_get_next_line(fd);
		y++;
	}
	return (matrix);
}

t_list	*ft_matrix_make(char *map_path)
{
	t_list	*matrix;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	line = ft_get_next_line(fd);
	matrix = NULL;
	matrix = ft_matrix_populate(fd, line, matrix);
	close(fd);
	return (matrix);
}

void	ft_matrix_rotate(t_list *matrix, int theta);
