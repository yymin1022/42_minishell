/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:02:34 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/22 21:24:35 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	*get_env_str(char *key, char *value)
{
	char	*res;

	res = ft_strjoin(key, "=");
	if (!res)
		return (NULL);
	res = ft_strjoin(res, value);
	if (!res)
		return (NULL);
	return (res);
}

static char	**get_env_str_list(t_env *env_list)
{
	char	*tmp;
	char	**res;
	size_t	idx;

	idx = 0;
	res = (char **)malloc(sizeof(char *) * env_getcnt(env_list));
	while (env_list)
	{
		tmp = get_env_str(env_list->key, env_list->value);
		res[idx] = ft_strdup(tmp);
		free(tmp);
		env_list = env_list->next;
		idx++;
	}
	return (res);
}

int	cmd_export(char **str, t_env *env_list)
{
	(void)env_list;
	get_env_str_list(env_list);
	printf("%s %s\n", str[0], str[1]);
	return (1);
}
