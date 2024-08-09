/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 13:31:30 by rmei              #+#    #+#             */
/*   Updated: 2024/07/17 18:21:30 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Adds a new node to the end of a singly-linked list */
t_list	*ft_lstadd_back(t_list *head, t_list *new_node)
{
	t_list	*node;

	if (!head)
		head = new_node;
	else
	{
		node = ft_lstlast(head);
		node->next = new_node;
	}
	return (head);
}
