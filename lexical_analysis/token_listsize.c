/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_listsize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isang-yun <isang-yun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:55:26 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/03 15:54:15 by isang-yun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_list.h"

int	token_listsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
