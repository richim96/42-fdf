/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/19 17:17:08 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_file_is_valid(char *map)
{
	char	*ext;
	char	*error_msg;

	ext = ".fdf";
	error_msg = "[ERROR]: Invalid file type - extension must be .fdf\n";
	while (*map && *map != '.')
		map++;
	while (*map == *ext && *map && *ext)
	{
		map++;
		ext++;
	}
	if (!*map && !*ext)
		return (1);
	write(2, error_msg, ft_strlen(error_msg));
	return (0);
}

static int	ft_map_is_valid(char *map)
{
	int		fd;
	int		bytes_read;
	char	*line;
	char	*error_msg;

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
	error_msg = "[ERROR]: Empty map\n";
	if (bytes_read == 0)
	{
		write(2, error_msg, ft_strlen(error_msg));
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	char	*map;
	char	*error_msg;

	error_msg = "[ERROR]: Invalid map argument\n";
	if (argc != 2)
	{
		write(2, error_msg, ft_strlen(error_msg));
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
