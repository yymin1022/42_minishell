/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_listutil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:11:54 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/04 15:13:23 by sangylee         ###   ########.fr       */
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

void	token_pushback(t_token **lst, t_token *new)
{
	t_token	*node;

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

int	is_tokenable_sep(char c)
{
	return (c == ' ' || c == '|' || c == '<' || c == '>' || c == '\0');
}
