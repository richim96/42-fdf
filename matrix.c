/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/16 15:23:40 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**ft_z_vector_normalize(char **z_vector)
{
	return (z_vector);
}

/* Returns 1 upon successfully adding the nodes for the current vector */
static int	ft_vector3D_fill(t_list **matrix, char **z_vector, int x, int y)
{
	t_list	*node;
	int		*content;

	while (*z_vector)
	{
		content = malloc(3);
		if (!content)
		{
			ft_lstclear(matrix, free);
			return (0);
		}
		content[0] = x++;
		content[1] = y;
		content[2] = ft_atoi(*z_vector);
		node = ft_lstnew(content);
		if (!node)
		{
			ft_lstclear(matrix, free);
			return (0);
		}
		ft_lstadd_back(matrix, node);
		z_vector++;
	}
	return (1);
}

static void	ft_matrix_fill(int fd, char *line, t_list **matrix)
{
	char	**z_vector;
	int		x;
	int		y;
	int		vector3D_fill;

	x = 0;
	y = 0;
	while (line)
	{
		z_vector = ft_z_vector_normalize(ft_split(line, ' '));
		free(line);
		vector3D_fill = ft_vector3D_fill(matrix, z_vector, x, y);
		if (!vector3D_fill)
			return ;
		y++;
		line = ft_get_next_line(fd);
	}
}

t_list	**ft_matrix_make(char *map_path)
{
	t_list	**matrix;
	t_list	*__init_node;
	char	*line;
	int		fd;

	fd = open(map_path, O_RDONLY);
	line = ft_get_next_line(fd);
	__init_node = NULL;
	matrix = &__init_node;
	ft_matrix_fill(fd, line, matrix);
	close(fd);
	return (matrix);
}

void	ft_matrix_rotate(t_list **matrix, int theta);
