/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 16:22:02 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (!*map && !*ext)
		return (1);
	ft_error_write("[ERROR]: Invalid file type - extension must be .fdf\n");
	return (0);
}

static int	ft_map_is_valid(char *map)
{
	int		fd;
	int		bytes_read;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		perror("[SYS_ERROR]");
		return (0);
	}
	line = malloc(1);
	bytes_read = read(fd, line, 1);
	free(line);
	close(fd);
	if (bytes_read == 0)
	{
		ft_error_write("[ERROR]: Empty map\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*map;

	if (argc != 2)
	{
		ft_error_write("[ERROR]: Invalid map argument\n");
		return (1);
	}
	map = argv[1];
	if (!ft_file_is_valid(map))
		return (1);
	if (!ft_map_is_valid(map))
		return (1);
	ft_map_show(map);
	return (0);
}
