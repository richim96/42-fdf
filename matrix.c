/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:39 by rmei              #+#    #+#             */
/*   Updated: 2024/07/19 12:57:39 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int 	ft_z_coord_get(char *z_data)
{
	char	**z_data_split;
	int		z_coord;
	int		i;

	z_data_split = ft_split(z_data, ',');
	z_coord = ft_atoi(z_data_split[0]);
	i = 0;
	while (z_data_split[i])
		free(z_data_split[i++]);
	free(z_data_split);
	return (z_coord);
}

//static int	ft_z_color_get(char *z_data)

/* Returns 1 upon successfully adding the nodes for the current vector */
static t_list	*ft_vector_add(t_list *head, char *line, int x, int y)
{
	t_list	*node_new;
	char	**z_data;
	int		*vector_new;
	int		i;

	i = 0;
	z_data = ft_split(line, ' ');
	while (z_data[i])
	{
		vector_new = malloc(4 * sizeof(int));
		if (!vector_new)
			ft_quit_on_matrix_failure(head);
		vector_new[0] = x++;
		vector_new[1] = y;
		vector_new[2] = ft_z_coord_get(z_data[i]);
		vector_new[3] = ft_hextoi(BASE_COLOR); //ft_z_color_get(z_data[i]);
		node_new = ft_lstnew(vector_new);
		if (!node_new)
			ft_quit_on_matrix_failure(head);
		head = ft_lstadd_back(head, node_new);
		free(z_data[i]);
		i++;
	}
	free(z_data);
	return (head);
}

static t_list	*ft_matrix_populate(int fd, char *line, t_list *head)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (line)
	{
		head = ft_vector_add(head, line, x, y);
		free(line);
		line = ft_get_next_line(fd);
		y++;
	}
	return (head);
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
