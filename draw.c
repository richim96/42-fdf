/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/08 16:15:36 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	ft_mlx_pixel_put(t_img img, int x, int y, unsigned int pixel_color)
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
	pixel_color = 0xFFFFFF;
	while (map_row)
	{
		while (x < img.img_width)
		{
			ft_mlx_pixel_put(img, x, y, pixel_color);
			ft_mlx_pixel_put(img, x++, img.img_height - 1, pixel_color);
		}
		while (y < img.img_height)
		{
			ft_mlx_pixel_put(img, x, y, pixel_color);
			ft_mlx_pixel_put(img, img.img_width - 1, y++, pixel_color);
		}
		free(map_row);
		map_row = ft_get_next_line(fd);
		break ;
	}
	//free(map_row);
}

void	ft_map_show(char *map_path)
{
	int		fd;
	char	*map_row;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;

	mlx_ptr = mlx_init();
	img.img_width = ft_cols_count(map_path) * 10;
	img.img_height = ft_rows_count(map_path) * 10;
	img.img_ptr = mlx_new_image(mlx_ptr, img.img_width, img.img_height);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr, &img.bits_per_pixel, &img.size_line, &img.endian);
	fd = open(map_path, O_RDONLY);
	map_row = ft_get_next_line(fd);
	ft_mlx_img_draw(img, fd, map_row);
	close(fd);
	win_ptr = mlx_new_window(
		mlx_ptr, img.img_width / 0.66, img.img_height / 0.66 , map_path);
	mlx_put_image_to_window(
		mlx_ptr,
		win_ptr,
		img.img_ptr,
		img.img_width / 0.66 * 0.16,
		img.img_height / 0.66 * 0.16);
	mlx_loop(mlx_ptr);
}
