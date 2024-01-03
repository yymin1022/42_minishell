/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_createnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:21:04 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/03 15:54:31 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"

t_list	*token_createnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
