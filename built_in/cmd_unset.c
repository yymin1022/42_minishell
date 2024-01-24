/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:02:34 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/25 01:21:11 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	is_target_env(char *str, char *env)
{
	size_t	i;

	i = 0;
	while (str[i] && env[i] && env[i] != '=')
	{
		if (str[i] != env[i])
			return (0);
		i++;
	}
	if (env[i] != '=' && str[i] != env[i])
		return (0);
	return (1);
}

static void	del_env(char *str, t_env **env_list)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env_list;
	if (is_target_env(str, cur->str))
	{
		*env_list = (*env_list)->next;
		four_times_free(cur->str, (char *)cur, 0, 0);
		return ;
	}
	prev = *env_list;
	while (cur)
	{
		if (is_target_env(str, cur->str))
		{
			prev->next = cur->next;
			four_times_free(cur->str, (char *)cur, 0, 0);
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
