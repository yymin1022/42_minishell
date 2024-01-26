/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:57:07 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/26 05:06:33 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	is_builtin(char **argv, t_env *env_list)
{
	if (!(argv[0]))
		return (0);
	else if (!ft_strcmp(argv[0], "cd"))
		return (printf("cd\n"));
	else if (!ft_strcmp(argv[0], "echo"))
		return (cmd_echo(argv));
	else if (!ft_strcmp(argv[0], "env"))
		return (cmd_env(env_list));
	else if (!ft_strcmp(argv[0], "exit"))
		exit (0);
	else if (!ft_strcmp(argv[0], "export"))
		return (cmd_export(argv, env_list));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (cmd_pwd());
	else if (!ft_strcmp(argv[0], "unset"))
		return (cmd_unset(argv, env_list));
	return (0);
}
