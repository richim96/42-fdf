/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/07/15 12:02:18 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
