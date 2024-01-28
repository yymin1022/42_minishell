/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 00:11:56 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/29 01:51:55 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static char	*get_home_path(t_env *env_list)
{
	char	*key;

	while (env_list)
	{
		key = get_env_key(env_list->str);
		if (key && ft_strcmp(key, "HOME") == 0)
		{
			free(key);
			return (get_env_value(env_list->str));
		}
		four_times_free(key, 0, 0, 0);
		env_list = env_list->next;
	}
	return (NULL);
}

static void	update_pwd_env(char *prev_path, t_env *env_list)
{
	char	*key;
	char	*new_path;

	new_path = getcwd(NULL, 0);
	while (env_list)
	{
		key = get_env_key(env_list->str);
		if (key && ft_strcmp(key, "PWD") == 0)
		{
			free(env_list->str);
			env_list->str = ft_strjoin("PWD=", new_path);
		}
		else if (key && ft_strcmp(key, "OLDPWD") == 0)
		{
			free(env_list->str);
			env_list->str = ft_strjoin("OLDPWD=", prev_path);
		}
		four_times_free(key, 0, 0, 0);
		env_list = env_list->next;
	}
	four_times_free(new_path, 0, 0, 0);
}

int	cmd_cd(char **argv, t_env *env_list)
{
	char	*home_path;
	char	*new_path;
	char	*prev_path;

	home_path = get_home_path(env_list);
	if (argv[1] == NULL || ft_strcmp(argv[1], "~") == 0)
		new_path = home_path;
	else if (argv[1][0] == '~')
		new_path = ft_strjoin(home_path, &argv[1][1]);
	else
		new_path = ft_strdup(argv[1]);
	if (new_path == NULL)
		return (0);
	prev_path = getcwd(NULL, 0);
	if (chdir(new_path) == 0)
		update_pwd_env(prev_path, env_list);
	else
	{
		four_times_free(prev_path, new_path, home_path, 0);
		ft_putstr_fd("pmshell: ", 2);
		perror("cd");
		return (0);
	}
	four_times_free(prev_path, new_path, home_path, 0);
	return (1);
}
