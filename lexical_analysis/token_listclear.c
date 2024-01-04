/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_listclear.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:19:14 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 15:06:15 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

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
