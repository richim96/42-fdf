/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:53:58 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 15:48:20 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Apply an isometric transformation on the map coordinates. */
void    ft_iso_transform(t_vec_3D **vecs, int width, int height)
{
    int         i;
    int         x;
    int         size;
    t_vec_3D    *v;
    
    i = 0;
    size = (I_HEIGHT) / (width + height);
    // if (size == 0)
    //     size = 1;
    size = 5;
    while (vecs[i])
    {
        v = vecs[i];
        x = v->x;
        v->x = (x - v->y) * cos(30) * size + I_WIDTH / 3;
        v->y = -v->z + (x + v->y) * sin(30) * size + I_HEIGHT / 3;
        i++;
    }
}
