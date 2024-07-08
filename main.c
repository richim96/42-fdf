/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/03 16:44:34 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wireframe.h"

static int	ft_file_is_valid(char *map)
{
	char	*ext;

	ext = ".fdf";
	while (*map && *map != '.')
		map++;
	while (*map == *ext && *map && *ext)
	{
		map++;
		ext++;
	}
	if (*map || *ext)
		return (0);
	return (1);
}

static int	ft_map_is_valid(char *map)
{
	int		fd;
	char	*line;
	size_t	n_rows;

	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	n_rows = ft_strlen(line);
	while (line)
	{
		if (ft_strlen(line) != n_rows || !ft_isnumstr(line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*map;

	if (argc != 2)
	{
		write(2, "[ERROR] : Invalid argument for map file path\n", 45);
		return (1);
	}
	map = argv[1];
	if (!ft_file_is_valid(map))
	{
		write(2, "[ERROR] : Invalid file type - extension must be .fdf\n", 53);
		return (1);
	}
	if (open(map, O_RDONLY) == -1)
	{
		perror("[SYS_ERROR]");
		return (1);
	}
	if (!ft_map_is_valid(map))
	{
		write(2, "[ERROR] : Invalid map formatting\n", 33);
		return (1);
	}
	ft_map_show(map);
	return (0);
}
