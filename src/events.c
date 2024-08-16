/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:09:21 by rmei              #+#    #+#             */
/*   Updated: 2024/08/13 16:00:18 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Initialize X11 events. */
void	ft_mlx_events_init(t_screen *screen)
{
	mlx_hook(screen->win_ptr, ON_DESTROY, MLX_MASK, ft_mlx_kill, screen);
	mlx_key_hook(screen->win_ptr, ft_keyhook, screen);
}

/* Free memory and terminate all X11 processes. */
int	ft_mlx_kill(t_screen *screen)
{
	int	i;

	if (screen->vecs)
	{
		i = 0;
		while (screen->vecs[i])
			free(screen->vecs[i++]);
		free(screen->vecs);
	}
	mlx_destroy_image(screen->mlx_ptr, screen->img->img_ptr);
	mlx_destroy_window(screen->mlx_ptr, screen->win_ptr);
	mlx_destroy_display(screen->mlx_ptr);
	free(screen->mlx_ptr);
	exit(0);
}

/* Key-based events. */
int	ft_keyhook(int key, t_screen *screen)
{
	if (key == X11LINUX_ESC || key == X11MACOS_ESC)
		ft_mlx_kill(screen);
	return (0);
}
