/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/07/08 16:15:00 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Check if a string is fully numeric, separted by spaces, tabs or new lines */
int	ft_isnumstr(char *s)
{
	while (*s)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (!*s)
			return (1);
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

/* Counts map columns from a given map file*/
int	ft_cols_count(char *map_path)
{
	int		fd;
	int		cols;
	char	*map_row;

	fd = open(map_path, O_RDONLY);
	map_row = ft_get_next_line(fd);
	cols = ft_strlen(map_row);
	free(map_row);
	close(fd);
	return (cols);
}

/* Counts map rows from a given map file */
int	ft_rows_count(char *map_path)
{
	int		fd;
	int		rows;
	char	*map_row;

	fd = open(map_path, O_RDONLY);
	rows = 0;
	map_row = ft_get_next_line(fd);
	while (map_row)
	{
		rows++;
		free(map_row);
		map_row = ft_get_next_line(fd);
	}
	free(map_row);
	close(fd);
	return (rows);
}
