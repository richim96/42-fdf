/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:24:40 by rmei              #+#    #+#             */
/*   Updated: 2024/08/02 20:29:31 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "macros.h"
# include "mlx.h"

/* STRUCTURES */
typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	pxl_color;
}	t_coord;

typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_coord	**coords;
}	t_screen;

/* FUNCTIONS  */
// - Draw
void	ft_map_show(char *map_path);

// - Coordinate manipulation
t_coord	**ft_coords_make(char *map, int fd);
//char	*ft_vector_rotate(char *vector, int theta);

// - Utils
int		ft_hextoi(char *hex);
int		ft_n_cols(char *vector);
int		ft_n_rows(char *map);
void	ft_write_error(char *error_msg);

// - Hooks
int		ft_mlx_kill(t_screen *screen);
int		ft_keyhook(int key, t_screen *screen);
int		ft_mousehook(int button, t_screen *screen);

#endif
