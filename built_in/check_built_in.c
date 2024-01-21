/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:57:07 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 16:01:44 by yonyoo           ###   ########seoul.kr  */
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
		return (printf("echo\n"));
	else if (!ft_strcmp(argv[0], "env"))
		return (cmd_env(env_list));
	else if (!ft_strcmp(argv[0], "exit"))
		exit (0);
	else if (!ft_strcmp(argv[0], "export"))
		return (printf("export\n"));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (cmd_pwd());
	else if (!ft_strcmp(argv[0], "unset"))
		return (printf("unset\n"));
	return (0);
}
