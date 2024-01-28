/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 01:32:00 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/30 13:44:03 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pm_shell.h"

void	print_argument_err(char *str)
{
	char	*tmp;

	tmp = ft_strjoin("Invalid Argument : ", str);
	if (!tmp)
		return ;
	ft_putendl_fd(tmp, 2);
	free(tmp);
}

void	update_env(char **str, char *new)
{
	free(*str);
	*str = ft_strdup(new);
}

char	**get_env_str_list(t_env *env_list)
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
