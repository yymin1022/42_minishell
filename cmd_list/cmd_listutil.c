/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_listutil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:31:50 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/14 17:37:24 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

t_cmd	*cmd_createnew(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->argv = 0;
	node->redirect = 0;
	node->prev = 0;
	node->next = 0;
	return (node);
}

void	cmd_pushback(t_cmd **lst, t_cmd *new_node)
{
	t_cmd	*node;

	if (*lst)
	{
		node = *lst;
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*lst = new_node;
}

void	cmd_listclear(t_cmd **lst)
{
	t_cmd	*node;
	t_cmd	*cur;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		node = cur;
		free(cur->argv);
		free(cur->redirect);
		cur = cur->next;
		free(node);
	}
	*lst = 0;
}
