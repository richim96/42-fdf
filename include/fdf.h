/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:24:40 by rmei              #+#    #+#             */
/*   Updated: 2024/08/13 13:04:24 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "mlx.h"

# include "macros.h"
# include "structs.h"

/* draw.c */

void		ft_map_draw(t_screen *screen);

/* vectors.c */

t_vec_3D	**ft_vectors_make(t_img *img, char *map);

/* transform.c */

void		ft_iso_transform(t_vec_3D **vecs, int width, int height);

/* utils.c */

int			ft_hextoi(char *hex);
void		ft_map_size_get(t_img *img, char *map);
void		ft_error_write(char *error_msg);
void		ft_nested_array_free(void **ptr, int pos, int reverse);

/* events.c */

void		ft_mlx_events_init(t_screen *screen);
int			ft_mlx_kill(t_screen *screen);
int			ft_keyhook(int key, t_screen *screen);

#endif
