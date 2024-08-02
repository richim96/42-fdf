/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:09:21 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 20:47:14 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Exit code must be 0 for success or 1 for failure */
int	ft_mlx_kill(t_screen *screen)
{
	int	i;

	i = 0;
	while (screen->coords[i])
		free(screen->coords[i++]);
	free(screen->coords);
	mlx_destroy_image(screen->mlx_ptr, screen->img->img_ptr);
	mlx_destroy_window(screen->mlx_ptr, screen->win_ptr);
	//mlx_destroy_display(screen->mlx_ptr);
	free(screen->mlx_ptr);
	exit(0);
}

int	ft_keyhook(int key, t_screen *screen)
{
	if (key == X11LINUX_ESC || key == X11MACOS_ESC)
		ft_mlx_kill(screen);
	return (0);
}

int	ft_mousehook(int button, t_screen *screen)
{
	if (!screen)
	{
		ft_printf("%i", button);
		write(2, "error\n", 6);
	}
	return (0);
}
