/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/07/03 17:02:28 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wireframe.h"

/* Check if a string is fully numeric, separted by spaces, tabs or new lines */
int	ft_isnumstr(char *s)
{
	while (*s)
	{
		while (*s == ' ' || *s == '\t' || *s == '\n')
			s++;
		if (!*s)
			return (1);
		if (!ft_isdigit(*s))
			return (0);
		s++;
	}
	return (1);
}

/* Convert 0-255 int values into an appropriate RBG int using bitshifting */
int	f_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
