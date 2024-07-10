/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/10 14:31:57 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_mlx_pixel_draw(t_img img, int x, int y, unsigned int pixel_color)
{
	int		bytes_per_pixel;
	int		pixel_offset;
	char	*coordinate;

	bytes_per_pixel = img.bits_per_pixel / 8;
	pixel_offset = y * img.size_line + x * bytes_per_pixel;
	coordinate = img.img_addr + pixel_offset;
	*(unsigned int *)coordinate = pixel_color;
}

static void	ft_mlx_img_draw(t_img img, int fd, char *map_row)
{
	int	x;
	int	y;
	int	z;
	int	pixel_color;

	x = 0;
	y = 0;
	z = ft_atoi(map_row);
	ft_printf("%i\n", z);
	pixel_color = 0xFFFFFF;
	while (map_row)
	{
		while (x < img.width)
		{
			ft_mlx_pixel_draw(img, x, y, pixel_color);
			ft_mlx_pixel_draw(img, x++, img.height - 1, pixel_color);
		}
		while (y < img.height)
		{
			ft_mlx_pixel_draw(img, x, y, pixel_color);
			ft_mlx_pixel_draw(img, img.width - 1, y++, pixel_color);
		}
		free(map_row);
		map_row = ft_get_next_line(fd);
		break ;
	}
	free(map_row);
}

static void	ft_mlx_events_init(t_screen *screen)
{
	mlx_hook(screen->win_ptr, ON_DESTROY, MLX_MASK, ft_mlx_kill, screen);
	mlx_key_hook(screen->win_ptr, ft_keyhook, screen);
	//mlx_mouse_hook(screen->win_ptr, ft_mousehook, screen);
}

void	ft_map_show(char *map_path)
{
	int			fd;
	char		*map_row;
	t_screen	screen;
	t_img		img;

	screen.mlx_ptr = mlx_init();
	screen.win_ptr = mlx_new_window(
			screen.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, map_path);
	screen.img = &img;
	img.width = WIN_WIDTH * 0.66;
	img.height = WIN_HEIGHT * 0.66;
	img.img_ptr = mlx_new_image(screen.mlx_ptr, img.width, img.height);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	fd = open(map_path, O_RDONLY);
	map_row = ft_get_next_line(fd);
	ft_mlx_img_draw(img, fd, map_row);
	close(fd);
	mlx_put_image_to_window(
		screen.mlx_ptr, screen.win_ptr,
		img.img_ptr, img.width * 0.25, img.height * 0.35);
	ft_mlx_events_init(&screen);
	mlx_loop(screen.mlx_ptr);
}
