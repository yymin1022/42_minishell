/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_createnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 11:21:04 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 15:05:44 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

t_token	*token_createnew(char *token_str, t_token_type token_type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = token_str;
	node->type = token_type;
	node->next = NULL;
	return (node);
}
