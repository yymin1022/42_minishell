/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangylee <sangylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/05 16:41:44 by sangylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static void	reset_fd_signal(int stdin_fd, int stdout_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		exit_msg("FD Error");
	if (dup2(stdout_fd, STDOUT_FILENO) == -1)
		exit_msg("FD Error");
	close(stdin_fd);
	close(stdout_fd);
	init_sig_handler();
}

static int	get_cmd_cnt(t_cmd *cmd_list)
{
	int	i;

	i = 0;
	while (cmd_list)
	{
		i++;
		cmd_list = cmd_list->next;
	}
	return (i);
}

void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list)
{
	int	cmd_cnt;
	int	stdin_fd;
	int	stdout_fd;
	pid_t	pid;

	cmd_cnt = get_cmd_cnt(cmd_list);
	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		g_status_code = 1;
		return ;
	}
	else if (pid == 0)
		exec_heredoc(cmd_list, env_list);
	signal(SIGINT, SIG_IGN);
	wait(&g_status_code);
	if (WIFEXITED(g_status_code))
		g_status_code = WEXITSTATUS(g_status_code);
	if (WIFSIGNALED(g_status_code))
	{
		g_status_code = 1;
		unlink_heredoc_tmp(cmd_list);
		reset_fd_signal(stdin_fd, stdout_fd);
		return ;
	}
	if (get_cmd_cnt(cmd_list) > 1)
		exec_multiple_cmd(cmd_list, env_list, cmd_cnt);
	else
		exec_single_cmd(cmd_list, env_list);
	unlink_heredoc_tmp(cmd_list);
	reset_fd_signal(stdin_fd, stdout_fd);
}
