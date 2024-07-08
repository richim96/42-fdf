/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/08 16:14:41 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_file_is_valid(char *map_path)
{
	char	*ext;

	ext = ".fdf";
	while (*map_path && *map_path != '.')
		map_path++;
	while (*map_path == *ext && *map_path && *ext)
	{
		map_path++;
		ext++;
	}
	if (*map_path || *ext)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*map_path;
	char	*error_msg;

	error_msg = "[ERROR] : Invalid argument for map file path\n";
	if (argc != 2)
	{
		write(2, error_msg, ft_strlen(error_msg));
		return (1);
	}
	map_path = argv[1];
	error_msg = "[ERROR] : Invalid file type - extension must be .fdf\n";
	if (!ft_file_is_valid(map_path))
	{
		write(2, error_msg, ft_strlen(error_msg));
		return (1);
	}
	if (open(map_path, O_RDONLY) == -1)
	{
		perror("[SYS_ERROR]");
		return (1);
	}
	ft_map_show(map_path);
	return (0);
}
