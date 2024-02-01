/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 00:41:03 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/02 03:28:24 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

void	exec_command(t_cmd *cmd, t_env *env_list)
{
	char	**env_str_list;
	char	**path_list;
	char	*full_cmd;

	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		exit(1);
	env_str_list = get_env_str_list(env_list);
	path_list = get_path_env(env_list);
	if (path_list == NULL || path_list[0] == NULL)
	{
		execve(cmd->argv[0], cmd->argv, env_str_list);
		exit_no_path(cmd->argv[0]);
	}
	full_cmd = get_full_path_cmd(cmd->argv[0], path_list);
	if (full_cmd == NULL)
		exit_not_found(cmd->argv[0]);
	execve(full_cmd, cmd->argv, env_str_list);
	free_2d_str_array(env_str_list);
	free_2d_str_array(path_list);
	exit_err(cmd->argv[0], 1);
}
