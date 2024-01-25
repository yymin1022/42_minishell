/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:24:51 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/25 18:25:12 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analysis.h"

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

int	is_target_env(char *str, char *env)
{
	size_t	i;

	i = 0;
	while (str[i] && env[i] && str[i] != '=' && env[i] != '=')
	{
		if (str[i] != env[i])
			return (0);
		i++;
	}
	if (str[i] != '=' && str[i] && env[i] != '=' && env[i])
		return (0);
	return (1);
}
