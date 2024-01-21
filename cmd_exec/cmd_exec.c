/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:39:09 by yonyoo            #+#    #+#             */
/*   Updated: 2024/01/21 17:06:00 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

static void	exec_cmd(char **argv, t_env *env_list)
{
	if (!argv || !(argv[0]))
		return ;
	if (!is_builtin(argv, env_list))
	{
		// 환경변수에서 실행
	}
}

void	exec_cmd_list(t_cmd *cmd_list, t_env *env_list)
{
	while (cmd_list)
	{
		if (cmd_list->argv)
			exec_cmd(cmd_list->argv, env_list);
		cmd_list = cmd_list->next;
	}
}
