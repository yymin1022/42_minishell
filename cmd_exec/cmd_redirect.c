/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonyoo <yonyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 19:58:11 by yonyoo            #+#    #+#             */
/*   Updated: 2024/02/04 22:39:56 by yonyoo           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_exec.h"

int	redirect_io(t_cmd *cmd)
{
	int			res;
	t_redirect	*redir;

	// if (cmd->redirect == NULL)
	// 	return (1);
	redir = cmd->redirect;
	printf("AA %s\n", redir->type);
	printf("BB %s\n", redir->file);
	res = 1;
	while (redir && res)
	{
		printf("AA %s\n", redir->type);
		printf("BB %s\n", redir->file);
		redir = cmd->next->redirect;
	}
	return (res);
}
