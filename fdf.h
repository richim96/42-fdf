/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:24:40 by rmei              #+#    #+#             */
/*   Updated: 2024/08/07 19:38:08 by rmei             ###   ########.fr       */
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
	int		max_x;
	int		max_y;
}	t_img;

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int pxl_color;
}	t_vector_3d;

typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_vector_3d	**vecs;
}	t_screen;

/* FUNCTIONS  */
// - Draw
void	ft_map_show(char *map_path);

// - Vectors
t_vector_3d	**ft_vectors_make(t_img *img, char *map);

// - Utils
int		ft_hextoi(char *hex);
void	ft_content_size_get(t_img *img, char *map);
void	ft_write_error(char *error_msg);
void	ft_double_ptr_free(void **ptr, int pos, int reverse);

// - Hooks
void	ft_mlx_events_init(t_screen *screen);
int		ft_mlx_kill(t_screen *screen);
int		ft_keyhook(int key, t_screen *screen);

#endif
