/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 05:46:11 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 16:03:32 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static void	exec_child_cmd(t_cmd *cmd, t_env *env_list)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit_err("fork", 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redirect_io(cmd);
		exec_command(cmd, env_list);
	}
	cmd_wait_child(pid, 1);
}

void	exec_single_cmd(t_cmd *cmd, t_env *env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	is_builtin(cmd->argv);
	if (is_builtin(cmd->argv))
	{
		redirect_io(cmd);
		g_status_code = exec_builtin(cmd->argv, env_list);
	}
	else
		exec_child_cmd(cmd, env_list);
}
