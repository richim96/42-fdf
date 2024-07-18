/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/18 14:22:56 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_file_is_valid(char *map_path)
{
	char	*ext;
	char	*error_msg;

	ext = ".fdf";
	error_msg = "[ERROR]: Invalid file type - extension must be .fdf\n";
	while (*map_path && *map_path != '.')
		map_path++;
	while (*map_path == *ext && *map_path && *ext)
	{
		map_path++;
		ext++;
	}
	if (!*map_path && !*ext)
		return (1);
	write(2, error_msg, ft_strlen(error_msg));
	return (0);
}

// TEMP FUNCTION
static int	ft_map_is_valid(char *map_path)
{
	int		fd;
	int		bytes_read;
	char	*line;
	char	*error_msg;

	fd = open(map_path, O_RDONLY);
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
	char	*map_path;
	char	*error_msg;

	error_msg = "[ERROR]: Invalid map argument\n";
	if (argc != 2)
	{
		write(2, error_msg, ft_strlen(error_msg));
		return (1);
	}
	map_path = argv[1];
	if (!ft_file_is_valid(map_path))
		return (1);
	if (!ft_map_is_valid(map_path))
		return (1);
	ft_map_show(map_path);
	return (0);
}
