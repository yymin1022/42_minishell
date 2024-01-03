/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:02:31 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/03 15:53:57 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"

void	token_pushback(t_list **lst, t_list *new)
{
	t_list	*node;

	if (*lst)
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}
