/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:53:58 by rmei              #+#    #+#             */
/*   Updated: 2024/08/12 21:44:06 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Apply an isometric transformation on the map coordinates. */
void    ft_iso_transform(t_vec_3D **vecs, int width, int height)
{
    int         i;
    int         x;
    int         a;
    float       zoom;
    t_vec_3D    *v;
    
    i = 0;
    a = 45;
    zoom = (I_HEIGHT) / (width + height);
    // if (size == 0)
    //     size = 1;
    zoom = 10;
    while (vecs[i])
    {
        v = vecs[i];
        x = v->x;
        v->x = (x * cos(a) - v->y * cos(a)) * zoom + I_WIDTH / 3;
        v->y = ((x * sin(a) + v->y * sin(a)) / 2 - v->z) * zoom + I_HEIGHT / 3;
        i++;
    }
}
