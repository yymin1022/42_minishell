/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:02:34 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/22 21:46:26 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static void	del_env(char *str, t_env **env_list)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env_list;
	if (ft_strcmp(str, cur->key) == 0)
	{
		*env_list = (*env_list)->next;
		four_times_free(cur->key, cur->value, (char *)cur, 0);
		return ;
	}
	prev = *env_list;
	while (cur)
	{
		if (ft_strcmp(str, cur->key) == 0)
		{
			prev->next = cur->next;
			four_times_free(cur->key, cur->value, (char *)cur, 0);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	cmd_unset(char **argv, t_env *env_list)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		del_env(argv[i], &env_list);
		i++;
	}
	return (1);
}
