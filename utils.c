/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:32:45 by rmei              #+#    #+#             */
/*   Updated: 2024/07/19 17:40:39 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Converts an hexadecimal (0xFFFFFF) number into decimal */
int	ft_hextoi(char *hex)
{
	int	n;
	int	n_pow;
	int	result;

	result = 0;
	if (hex[1] == 'x')
		hex += 2;
	n_pow = ft_strlen(hex) - 1;
	while (*hex)
	{
		if (ft_isalpha(*hex))
			n = ft_tolower(*hex) - 'a' + 10;
		else
			n = *hex - '0';
		result += n * pow(16, n_pow);
		n_pow--;
		hex++;
	}
	return (result);
}

/* Counts the matrix columns */
int	ft_n_cols(char **vector)
{
	int	count;

	count = 0;
	while (*(vector++))
		count++;
	return (count);
}

/* Counts the matrix rows */
int	ft_n_rows(char *map)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(map, O_RDONLY);
	line = ft_get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = ft_get_next_line(fd);
	}
	close(fd);
	return (count);
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
