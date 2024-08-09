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

/* Applies an isometric transformation to the map vectors */
void ft_iso_transform(t_vector_3d **vecs, int max_x, int max_y)
{
    int         i;
    int         x;
    int         size;
    t_vector_3d *vec;
    
    i = 0;
    size = (I_HEIGHT) / (max_x * max_y);
    if (size == 0)
        size = 3;
    printf("%i\n", size);
    while (vecs[i])
    {
        vec = vecs[i];
        x = vec->x;
        vec->x = (x - vec->y) * size + I_WIDTH / 2;
        vec->y = ((x + vec->y) / 2 - vec->z) * size + I_HEIGHT / 4;
        i++;
    }
}
