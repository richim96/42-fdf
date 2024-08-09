/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 20:25:43 by rmei              #+#    #+#             */
/*   Updated: 2024/07/17 18:28:07 by rmei             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Adds a new node to the beginning of a singly-linked list */
t_list	*ft_lstadd_front(t_list *head, t_list *new_node)
{
	new_node->next = head;
	return (new_node);
}
