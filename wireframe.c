/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:14:12 by rmei              #+#    #+#             */
/*   Updated: 2024/07/03 17:23:54 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wireframe.h"

static void		ft_map_size_get(int *width, int *height)
{
	int		fd;
	char	*row;
	char	*tmp;
	
	fd = open(map, O_RDONLY);
	row = ft_get_next_line(fd);
	while (row)
	{
		height++;
		tmp = row;
		while (*tmp)
	}
	close(fd);
}
static t_img	ft_img_make(void *mlx_ptr)
{
	t_img	img;

	img.img_ptr = mlx_new_image(mlx_ptr, 500, 375);
	img.img_addr = mlx_get_data_addr(
			img.img_ptr,
			&img.bits_per_pixel,
			&img.size_line,
			&img.endian
			);
	return (img);
}

void	ft_map_show(char *map)
{
	int		width;
	int		height;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;

	width = 0;
	height = 0;
	ft_map_size_get(&width, &height);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 800, map);
	img = ft_img_make(mlx_ptr);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img_ptr, 70, 70);
	mlx_loop(mlx_ptr);
}
