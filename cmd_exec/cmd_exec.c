/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/03 02:23:11 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

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

	cmd_cnt = get_cmd_cnt(cmd_list);
	// exec_heredoc(cmd_list, env_list);
	if (get_cmd_cnt(cmd_list) > 1)
		exec_multiple_cmd(cmd_list, env_list, cmd_cnt);
	else
		exec_single_cmd(cmd_list, env_list);
	// unlink_heredoc_tmp(cmd_list);
}
