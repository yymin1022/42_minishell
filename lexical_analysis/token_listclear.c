/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_listclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:19:14 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/03 15:53:34 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"

void	token_listclear(t_list **lst, void (*del)(void *))
{
	t_list	*node;
	t_list	*cur;

	if (!del || !lst)
		return ;
	cur = *lst;
	while (cur)
	{
		node = cur;
		del(cur->content);
		cur = cur->next;
		free(node);
	}
	*lst = NULL;
}
