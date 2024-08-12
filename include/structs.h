/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:21:27 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 12:34:44 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 3D vector data. */
typedef struct s_vec_3D
{
	int	x;
	int	y;
	int	z;
	int color;
}	t_vec_3D;

/* X11 image details. */
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

/* X11 screen info and content. */
typedef struct s_screen
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*img;
	t_vec_3D	**vecs;
}	t_screen;
