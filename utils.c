/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/07/18 16:37:36 by rmei             ###   ########.fr       */
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

/* If the matrix creation fails, frees all memory and quits the program */ 
void	ft_quit_on_matrix_failure(t_list *matrix)
{
	char	*error_msg;
	
	error_msg = "[ERROR] : Matrix initialization failed\n";
	ft_lstclear(&matrix, free);
	write(2, error_msg, ft_strlen(error_msg));
	exit (1);
}
