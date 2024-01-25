/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:02:34 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/26 01:31:40 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	is_in_env(char *str, t_env *env_list)
{
	while (env_list)
	{
		if (is_target_env(str, env_list->str))
		{
			if (!is_value_available(env_list->str)
				|| (is_value_available(env_list->str)
					&& is_value_available(str)))
			{
				free(env_list->str);
				env_list->str = ft_strdup(str);
				return (1);
			}
			if (is_value_available(env_list->str))
				return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

static void	print_env_str_list(char **env_list)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 0;
	while (env_list[i])
	{
		key = get_env_key(env_list[i]);
		value = get_env_value(env_list[i]);
		if (value)
			printf("declare -x %s=\"%s\"\n", key, value);
		else
			printf("declare -x %s\n", key);
		four_times_free(env_list[i], key, value, 0);
		i++;
	}
	free(env_list);
}

static void	sort_env_str_list(char **env_list, size_t cnt)
{
	char	*tmp;
	int		is_ordered;
	size_t	i;

	is_ordered = 0;
	while (env_list && !is_ordered)
	{
		i = 0;
		is_ordered = 1;
		while (i < cnt - 1)
		{
			if (ft_strcmp(env_list[i], env_list[i + 1]) > 0)
			{
				tmp = env_list[i];
				env_list[i] = env_list[i + 1];
				env_list[i + 1] = tmp;
				is_ordered = 0;
			}
			i++;
		}
		cnt--;
	}
}

static char	**get_env_str_list(t_env *env_list)
{
	char	**res;
	size_t	idx;

	idx = 0;
	res = (char **)malloc(sizeof(char *) * (env_getcnt(env_list) + 1));
	while (env_list)
	{
		res[idx] = ft_strdup(env_list->str);
		env_list = env_list->next;
		idx++;
	}
	res[idx] = NULL;
	return (res);
}

int	cmd_export(char **str, t_env *env_list)
{
	char	**env_str_list;
	size_t	i;

	if (!str[1])
	{
		env_str_list = get_env_str_list(env_list);
		sort_env_str_list(env_str_list, env_getcnt(env_list));
		print_env_str_list(env_str_list);
		return (1);
	}
	i = 1;
	while (str[i])
	{
		if (!is_valid_env_key(str[i], 0))
			print_argument_err(str[i]);
		else if (!is_in_env(str[i], env_list))
			env_pushback(&env_list, env_createnew(str[i]));
		i++;
	}
	return (1);
}
