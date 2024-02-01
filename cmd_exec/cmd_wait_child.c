/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_wait_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:16:26 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/02 00:53:44 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

extern int	g_status_code;

void	cmd_wait_child(pid_t pid_parent, int cmd_cnt)
{
	int		i;
	int		status;
	int		is_print_err;
	pid_t	pid_child;

	i = 0;
	is_print_err = 0;
	while (i < cmd_cnt)
	{
		pid_child = waitpid(-1, &status, 0);
		if (WIFSIGNALED(status) && ++is_print_err)
		{
			if (WTERMSIG(status) == SIGINT && is_print_err)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGQUIT && is_print_err)
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			if (pid_child == pid_parent)
				g_status_code = 128 + WTERMSIG(status);
		}
		else if (pid_child == pid_parent)
			g_status_code = WEXITSTATUS(status);
		i++;
	}
}
