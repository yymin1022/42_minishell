/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/03 02:21:52 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

extern int	g_status_code;

static int	is_multiple_cmd(t_cmd *cmd_list)
{
	if (cmd_list->next == NULL && cmd_list->redirect == NULL)
		return (0);
	return (1);
}

void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list)
{
	//exec_heredoc(cmd_list, env_list);
	while (cmd_list)
	{
		if (is_multiple_cmd(cmd_list))
			exec_multiple_cmd(cmd_list, env_list);
		else
			exec_single_cmd(cmd_list, env_list);
		cmd_list = cmd_list->next;
	}
	unlink_heredoc_tmp(cmd_list);
}
