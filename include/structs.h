/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:21:27 by rmei              #+#    #+#             */
/*   Updated: 2024/08/16 12:36:09 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Bresenham line info */
typedef struct s_bres_line
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	e;
	int	e2;
	int	color;
}	t_bres_line;

/* Smallest and largest coordinate points of a matrix. */
typedef struct s_limits
{
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
}	t_limits;

/* 3D vector data. */
typedef struct s_vec_3D
{
	float	x;
	float	y;
	int		z;
	int		color;
}	t_vec_3D;

/* X11 image details. */
typedef struct s_img
{
	void	*img_ptr;
	char	*img_addr;
	int		bits_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

/* X11 screen info and content. */
typedef struct s_screen
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		*img;
	t_vec_3D	**vecs;
}	t_screen;
