/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_single.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 05:46:11 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/02 00:59:16 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

extern int	g_status_code;

static int	exec_child_cmd(t_cmd *cmd, t_env *env_list)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	(void)cmd;
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exec_command(cmd, env_list);
	}
	cmd_wait_child(pid, 1);
	return (1);
}

void	exec_single_cmd(t_cmd *cmd, t_env *env_list)
{
	int	exit_code;

	(void)cmd;
	(void)env_list;
	exit_code = 0;
	signal(SIGINT, SIG_DFL);
	if (is_builtin(cmd->argv))
		exit_code = exec_builtin(cmd->argv, env_list);
	else
		exit_code = exec_child_cmd(cmd, env_list);
	g_status_code = exit_code;
}
