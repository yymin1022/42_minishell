/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_listutil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:11:54 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/25 01:03:27 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analysis.h"

t_env	*make_envlist(char **env)
{
	int		i;
	t_env	*env_list;

	i = -1;
	env_list = NULL;
	while (env[++i])
		env_pushback(&env_list, env_createnew(env[i]));
	return (env_list);
}

t_env	*env_createnew(char *s)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->str = ft_strdup(s);
	node->next = NULL;
	return (node);
}

void	env_pushback(t_env **lst, t_env *new_node)
{
	t_env	*node;

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

void	env_listclear(t_env **lst)
{
	t_env	*node;
	t_env	*cur;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		node = cur;
		free(cur->str);
		cur = cur->next;
		free(node);
	}
	*lst = NULL;
}

size_t	env_getcnt(t_env *lst)
{
	size_t	idx;

	idx = 0;
	while (lst)
	{
		lst = lst->next;
		idx++;
	}
	return (idx);
}
