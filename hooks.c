/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:09:21 by rmei              #+#    #+#             */
/*   Updated: 2024/07/09 13:45:52 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_mlx_kill(t_screen *screen)
{
	mlx_destroy_image(screen->mlx_ptr, screen->img->img_ptr);
	mlx_destroy_window(screen->mlx_ptr, screen->win_ptr);
	exit(0);
}

int	ft_keyhook(int key, t_screen *screen)
{
	if (key == 65307)
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
