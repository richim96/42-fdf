/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:53:58 by rmei              #+#    #+#             */
/*   Updated: 2024/08/09 20:23:37 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Apply an isometric transformation on the map coordinates. */
void ft_iso_transform(t_vector_3d **vecs, int width, int height)
{
    int         i;
    int         x;
    int         size;
    t_vector_3d *vec;
    
    i = 0;
    size = (I_HEIGHT) / (width + height);
    // if (size == 0)
    //     size = 1;
    size = 10;
    while (vecs[i])
    {
        vec = vecs[i];
        x = vec->x;
        vec->x = (x - vec->y) * size + I_WIDTH / 2;
        vec->y = ((x + vec->y) / 2 - vec->z) * size + I_HEIGHT / 5;
        i++;
    }
}
