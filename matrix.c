/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/15 13:07:21 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	**ft_vectors_normalize(char **vectors)
{
	return (vectors);
}

/* Returns 1 upon successfully adding the nodes for the current x coordinate */
static int	ft_xcoord_fill(t_list **matrix, char **vectors, int content[])
{
	t_list	*node;
	int		y;

	y = 0;
	while (*vectors)
	{
		content[1] = y++;
		content[2] = ft_atoi(*(vectors++));
		node = ft_lstnew(&content);
		if (!node)
		{
			ft_lstclear(matrix, NULL);
			return (0);
		}
		ft_lstadd_back(matrix, node);
	}
	return (1);
}

static void	ft_matrix_fill(int fd, char *line, t_list **matrix)
{
	char	**vectors;
	int		is_x_success;
	int		content[3];
	int		x;

	x = 0;
	while (line)
	{
		content[0] = x++;
		vectors = ft_vectors_normalize(ft_split(line, ' '));
		free(line);
		is_x_success = ft_xcoord_fill(matrix, vectors, content);
		if (!is_x_success)
			return ;
		line = ft_get_next_line(fd);
	}
}

t_list	**ft_matrix_make(char *map_path)
{
	t_list	**matrix;
	char	*line;
	int		fd;

	matrix = (t_list **) malloc (sizeof(t_list *));
	if (!matrix)
		return (NULL);
	fd = open(map_path, O_RDONLY);
	line = ft_get_next_line(fd);
	ft_matrix_fill(fd, line, matrix);
	close(fd);
	return (matrix);
}

void	ft_matrix_rotate(t_list **matrix, int theta);
