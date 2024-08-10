/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:27:12 by rmei              #+#    #+#             */
/*   Updated: 2024/08/10 14:17:47 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Assess file validity. */
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

/* Assess map validity. */
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

/* Open a X11 window and render the map. */
static void	ft_screen_init(char *map)
{
	t_screen	screen;
	t_img		img;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(
			screen.mlx_ptr, W_WIDTH, W_HEIGHT, map);
	img.img_ptr = mlx_new_image(screen.mlx_ptr, W_WIDTH, W_HEIGHT);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	ft_map_size_get(&img, map);
	screen.img = &img;
	screen.vecs = ft_vectors_make(screen.img, map);
	if (!screen.vecs)
	{
		ft_error_write("[ERROR]: Not enough memory available for this map\n");
		ft_mlx_kill(&screen);
	}
	ft_mlx_events_init(&screen);
	ft_map_draw(&screen);
	mlx_loop(screen.mlx_ptr);
}

/* ----- MAIN ----- */
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
	ft_screen_init(map);
	return (0);
}
