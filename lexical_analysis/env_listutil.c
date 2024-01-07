/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_listutil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:11:54 by sangylee          #+#    #+#             */
/*   Updated: 2024/01/07 09:32:03 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pm_shell.h"

t_env	*make_envlist(char **env)
{
	int		i;
	char	*key;
	char	*value;
	char	*equal_idx;
	t_env	*env_list;

	i = -1;
	env_list = NULL;
	while (env[++i])
	{
		equal_idx = ft_strchr(env[i], '=');
		key = ft_substr(env[i], 0, equal_idx - env[i]);
		value = ft_strdup(equal_idx + 1);
		env_pushback(&env_list, env_createnew(key, value));
	}
	return (env_list);
}

t_env	*env_createnew(char *key, char *value)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	env_pushback(t_env **lst, t_env *new)
{
	t_env	*node;

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
		free(cur->key);
		free(cur->value);
		cur = cur->next;
		free(node);
	}
	*lst = NULL;
}
