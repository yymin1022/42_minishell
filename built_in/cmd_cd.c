/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 00:11:56 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 20:46:07 by sangylee         ###   ########.fr       */
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

static char	*get_oldpwd(t_env *env_list)
{
	char	*key;

	while (env_list)
	{
		key = get_env_key(env_list->str);
		if (key && ft_strcmp(key, "OLDPWD") == 0)
		{
			free(key);
			return (get_env_value(env_list->str));
		}
		four_times_free(key, 0, 0, 0);
		env_list = env_list->next;
	}
	return (NULL);
}

static int	update_oldpwd(char *prev_path, t_env *env_list)
{
	char	*key;
	int		is_oldpwd_found;
	t_env	*node;

	is_oldpwd_found = 0;
	node = env_list;
	while (node)
	{
		key = get_env_key(node->str);
		if (key && ft_strcmp(key, "OLDPWD") == 0 && ++is_oldpwd_found)
			update_env(&(node->str), prev_path);
		four_times_free(key, 0, 0, 0);
		node = node->next;
	}
	if (!is_oldpwd_found)
		env_pushback(&env_list, env_createnew(prev_path));
	four_times_free(prev_path, 0, 0, 0);
	return (1);
}

static int	update_pwd(t_env *env_list)
{
	char	*key;
	char	*new_path;
	char	*tmp;
	int		is_pwd_found;
	t_env	*node;

	is_pwd_found = 0;
	node = env_list;
	tmp = getcwd(NULL, 0);
	new_path = ft_strjoin("PWD=", tmp);
	while (node)
	{
		key = get_env_key(node->str);
		if (key && ft_strcmp(key, "PWD") == 0 && ++is_pwd_found)
			update_env(&(node->str), new_path);
		four_times_free(key, 0, 0, 0);
		node = node->next;
	}
	if (!is_pwd_found)
		env_pushback(&env_list, env_createnew(new_path));
	four_times_free(new_path, tmp, 0, 0);
	return (1);
}

int	cmd_cd(char **argv, t_env *env_list)
{
	char	*home_path;
	char	*new_path;
	char	*prev_path;

	home_path = get_home_path(env_list);
	if (argv[1] == NULL || argv[1][0] == '~')
	{
		if (argv[1] == NULL)
			new_path = ft_strdup(home_path);
		else
			new_path = ft_strjoin(home_path, &argv[1][1]);
	}
	else if (ft_strcmp(argv[1], "-") == 0)
		new_path = get_oldpwd(env_list);
	else
		new_path = ft_strdup(argv[1]);
	if (new_path == NULL)
		return (0);
	prev_path = getcwd(NULL, 0);
	if (chdir(new_path) != 0
		|| !update_pwd(env_list)
		|| !update_oldpwd(ft_strjoin("OLDPWD=", prev_path), env_list))
	{
		four_times_free(prev_path, new_path, home_path, 0);
		ft_putstr_fd("pmshell: ", 2);
		perror("cd");
		return (0);
	}
	four_times_free(prev_path, new_path, home_path, 0);
	return (1);
}
