/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:24:40 by rmei              #+#    #+#             */
/*   Updated: 2024/07/09 13:51:15 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdio.h>

# include "libft.h"
# include "mlx.h"

/* MACROS */
// - Screen
# define WIN_WIDTH 720
# define WIN_HEIGHT 480

// - EVENTS
# define ON_DESTROY 17
# define MLX_MASK 0

/* STRUCTURES */
typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
}	t_screen;

/* FUNCTIONS  */
// - Main
void	ft_map_show(char *map_path);

// - Utils
int		ft_isnumstr(char *s);
int		ft_cols_count(char *map_path);
int		ft_rows_count(char *map_path);

// - Hooks
int		ft_mlx_kill(t_screen *screen);
int		ft_keyhook(int key, t_screen *screen);
int		ft_mousehook(int button, t_screen *screen);

#endif
