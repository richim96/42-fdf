/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:24:40 by rmei              #+#    #+#             */
/*   Updated: 2024/08/09 20:18:27 by rmei             ###   ########.fr       */
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
	int		width;
	int		height;
}	t_img;

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
	int color;
}	t_vector_3d;

typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_vector_3d	**vecs;
}	t_screen;

/* FUNCTIONS  */
// - draw.c
void	ft_map_show(char *map_path);

// - vectors.c
t_vector_3d	**ft_vectors_make(t_img *img, char *map);

// - transform.c
void ft_iso_transform(t_vector_3d **vecs, int width, int height);

// - utils.c
int		ft_hextoi(char *hex);
void	ft_map_size_get(t_img *img, char *map);
void	ft_error_write(char *error_msg);
void	ft_2D_array_free(void **ptr, int pos, int reverse);

//  - mlx_events.c
void	ft_mlx_events_init(t_screen *screen);
int		ft_mlx_kill(t_screen *screen);
int		ft_keyhook(int key, t_screen *screen);

#endif
