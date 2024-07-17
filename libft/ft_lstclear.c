/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:11:07 by rmei              #+#    #+#             */
/*   Updated: 2024/07/17 18:33:14 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Frees a singly-linked list from all nodes */
void	ft_lstclear(t_list *head, void (*del)(void *))
{
	if (head->next)
		ft_lstclear(head->next, del);
	ft_lstdelone(head, del);
}
